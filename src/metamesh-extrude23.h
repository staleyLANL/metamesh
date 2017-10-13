/* -*- C++ -*- */

#ifndef METAMESH_EXTRUDE23
#define METAMESH_EXTRUDE23

/*

This file provides functionality for 2-form to 3-form extrusions.

Variants:

mesh<node,edge<node>,face<node>> to mesh<node,edge<node>,face<node>,cell<node>>

   layer:   node       to node
   filling: node       to edge<node>
   layer:   edge<node> to edge<node>
   filling: edge<node> to face<node>
   layer:   face<node> to face<node>
   filling: face<node> to cell<node>

mesh<node,edge<node>,face<node>> to mesh<node,edge<node>,face<node>,cell<edge>>

   layer:   node       to node
   filling: node       to edge<node>
   layer:   edge<node> to edge<node>
   filling: edge<node> to face<node>
   layer:   face<node> to face<node>
   filling: face<node> to cell<edge>

mesh<node,edge<node>,face<node>> to mesh<node,edge<node>,face<node>,cell<face>>

   layer:   node       to node
   filling: node       to edge<node>
   layer:   edge<node> to edge<node>
   filling: edge<node> to face<node>
   layer:   face<node> to face<node>
   filling: face<node> to cell<face>

mesh<node,edge<node>,face<edge>> to mesh<node,edge<node>,face<edge>,cell<node>>

   layer:   node       to node
   filling: node       to edge<node>
   layer:   edge<node> to edge<node>
   filling: edge<node> to face<edge>
   layer:   face<edge> to face<edge>
   filling: face<edge> to cell<node>

mesh<node,edge<node>,face<edge>> to mesh<node,edge<node>,face<edge>,cell<edge>>

   layer:   node       to node
   filling: node       to edge<node>
   layer:   edge<node> to edge<node>
   filling: edge<node> to face<edge>
   layer:   face<edge> to face<edge>
   filling: face<edge> to cell<edge>

mesh<node,edge<node>,face<edge>> to mesh<node,edge<node>,face<edge>,cell<face>>

   layer:   node       to node
   filling: node       to edge<node>
   layer:   edge<node> to edge<node>
   filling: edge<node> to face<edge>
   layer:   face<edge> to face<edge>
   filling: face<edge> to cell<face>

------------------------
------------------------

Required bookkeeping for each face/cell variant:

   ---------------------------------------------
      face<node>           cell<node>
         NONE                 NONE
   ---------------------------------------------
      face<node>           cell<edge>
         NONE                 n2e (e filling)
                              f2e (e layer)
   ---------------------------------------------
      face<node>           cell<face>
         NONE                 e2f (f filling)
                              f2e (e layer)
   ---------------------------------------------
      face<edge>           cell<node>
         n2e (e filling)      NONE
   ---------------------------------------------
      face<edge>           cell<edge>
         n2e (e filling)      n2e (e filling)
   ---------------------------------------------
      face<edge>           cell<face>
         n2e (e filling)      e2f (f filling)
   ---------------------------------------------
*/

// Whole file
namespace metamesh {
namespace internal {



// =============================================================================
// extrude_info: 2-to-3
// =============================================================================

// 3 = output form
template<class IMESH, class OMESH>
class extrude_info<IMESH,OMESH,3> {

   using onode = typename OMESH::node_t;

public:

   // ------------------------
   // data
   // ------------------------

   // number of nodes/edges/faces in input mesh; loopers
   const std::size_t nnode;  const loop n;
   const std::size_t nedge;  const loop e;
   const std::size_t nface;  const loop f;

   // index+1's in output mesh; 0 = uninitialized
   std::vector<std::size_t>
      ncurr, nprev, ninit,
      ecurr, eprev, einit,
      fcurr, fprev, finit;

   // proposed new layer
   std::vector<onode> proposed;  // nodes themselves
   std::vector< bool> nodeison;  // nodes on/true?
   std::vector< bool> edgeison;  // edges on/true?
   std::vector< bool> faceison;  // faces on/true?

   // filling
   std::vector<std::size_t>
      n2e,  // for each input node, mesh.edge index of its filling edge
      e2f;  // for each input edge, mesh.face index of its filling face

   // qqq Need comment here
   std::vector<
      std::pair<std::vector<std::size_t>,std::vector<std::size_t>>
   > e2fsides, e2fbegin;  // #=nedge, swept to faces

   std::vector<
      std::vector<std::size_t>
   > f2csides, f2cbegin;  // #=nface, swept to cells

   std::vector<
      std::vector<std::size_t>
   > f2e;  // faces --> its own edges; overhead


   // ------------------------
   // constructor
   // ------------------------

   explicit extrude_info(
      const std::size_t _nnode,
      const std::size_t _nedge,
      const std::size_t _nface,
      const bool face_terms_is_edge,
      const bool cell_terms_is_edge,
      const bool cell_terms_is_face,
      const bool face_terms_is_node,
      const bool cell_terms_is_node
   ) :
      nnode(_nnode), n(nnode),
      nedge(_nedge), e(nedge),
      nface(_nface), f(nface),

      ncurr(nnode,0), nprev(nnode,0), ninit(nnode,0),
      ecurr(nedge,0), eprev(nedge,0), einit(nedge,0),
      fcurr(nface,0), fprev(nface,0), finit(nface,0),

      proposed(nnode),
      nodeison(nnode),
      edgeison(nedge),
      faceison(nface),

      // qqq I should carefully vet and document each of the following, for both
      // 1-2 and 2-3. Looking at this now, several years after I first wrote the
      // code, it seems strange that some things are vec<pair<vec,vec>>, while
      // others are vec<vec>. It may all be correct, but needs review.

      // n2e: need iff face<edge> || cell<edge> (out.something is edge-based)
      n2e(face_terms_is_edge ||
          cell_terms_is_edge ? nnode : 0, 0),

      // e2f: need iff cell<face> (out.something is face-based)
      e2f(cell_terms_is_face ? nedge : 0, 0),

      // For each input edge, e2fsides collects up either the side-nodes
      // or side-edges that will be part of the edge's eventual swept face.
      e2fsides(nedge), e2fbegin(nedge),

      // nface because face extrusion creates cells
      f2csides(nface), f2cbegin(nface),

      // f2e: need iff face<node> && !cell<node>
      f2e(face_terms_is_node &&
         !cell_terms_is_node ? nface : 0)
   { }
};



// =============================================================================
// Macros
// =============================================================================

// extrude_logic_23_template
#define extrude_logic_23_template\
   template<\
      class inode, class iedge, class iface, class icell, class ibase,\
      class onode, class oedge, class oface, class ocell, class obase,\
      class PATH,\
      class NODE_ON, class N2N, class N2E,\
      class EDGE_ON, class E2E, class E2F,\
      class FACE_ON, class F2F, class F2C\
   >

// extrude_logic_23_type
#define extrude_logic_23_type\
   extrude_logic_23<\
      inode, iedge, iface, icell, ibase,\
      onode, oedge, oface, ocell, obase,\
      PATH,\
      NODE_ON, N2N, N2E,\
      EDGE_ON, E2E, E2F,\
      FACE_ON, F2F, F2C\
   >

// extrude_logic_23_function
#define extrude_logic_23_function(fun)\
   extrude_logic_23_template\
   void extrude_logic_23_type::fun(\
      const std::size_t iteration,\
      const bool tie, const bool trim, const bool wrap\
   )



// =============================================================================
// extrude_logic_23
// Function object; an instance is sent to the general extrude_logic()
// =============================================================================

extrude_logic_23_template
class extrude_logic_23 :
   public internal::extrude_info<
      metamesh::mesh<inode,iedge,iface,icell,ibase,2>,
      metamesh::mesh<onode,oedge,oface,ocell,obase,3>,
      3
   >
{
public:

   using extrude_info = internal::extrude_info<
      metamesh::mesh<inode,iedge,iface,icell,ibase,2>,
      metamesh::mesh<onode,oedge,oface,ocell,obase,3>, 3
   >;

   using extrude_info::nnode;
   using extrude_info::n;
   using extrude_info::ncurr;
   using extrude_info::nprev;
   using extrude_info::ninit;
   using extrude_info::proposed;
   using extrude_info::nodeison;

   using extrude_info::nedge;
   using extrude_info::e;
   using extrude_info::ecurr;
   using extrude_info::eprev;
   using extrude_info::einit;
   using extrude_info::edgeison;
   using extrude_info::n2e;
   using extrude_info::e2fsides;
   using extrude_info::e2fbegin;

   using extrude_info::nface;
   using extrude_info::f;
   using extrude_info::fcurr;
   using extrude_info::fprev;
   using extrude_info::finit;
   using extrude_info::faceison;
   using extrude_info::e2f;
   using extrude_info::f2e;
   using extrude_info::f2csides;
   using extrude_info::f2cbegin;

private:

   // types
   using value_t      = typename onode::value_t;  // output node value_t
   using idx_vec      = std::vector<std::size_t>;
   using idx_vec_pair = std::pair<idx_vec,idx_vec>;
   using face_terms   = typename oface::basis_t;  // node | edge
   using cell_terms   = typename ocell::basis_t;  // node | edge | face

   // meshes
   const mesh<inode,iedge,iface,icell,ibase,2> &in;
   /* */ mesh<onode,oedge,oface,ocell,obase,3> &out;

   // functors
   const PATH &path;
   const NODE_ON &node_on;  const N2N &node2node;  const N2E &node2edge;
   const EDGE_ON &edge_on;  const E2E &edge2edge;  const E2F &edge2face;
   const FACE_ON &face_on;  const F2F &face2face;  const F2C &face2cell;

   // eps, length scaling
   const value_t eps;  value_t scaling;

   // for convenience
   // qqq...
   // no curr_node?
   // no init_edge?
   // no init_face?
   inline const onode &init_node(const std::size_t n) const
      { return out.node[ninit[n]-1]; }
   inline const onode &prev_node(const std::size_t n) const
      { return out.node[nprev[n]-1]; }

   inline const oedge &prev_edge(const std::size_t e) const
      { return out.edge[eprev[e]-1]; }
   inline const oedge &curr_edge(const std::size_t e) const
      { return out.edge[ecurr[e]-1]; }

   inline const oface &prev_face(const std::size_t f) const
      { return out.face[fprev[f]-1]; }
   inline const oface &curr_face(const std::size_t f) const
      { return out.face[fcurr[f]-1]; }

   // submit_edge_if_appropriate
   bool submit_edge_if_appropriate(
      const std::size_t nnode, const std::size_t iteration, const bool trim
      // qqq Compare w/function below; uses ncurr and nprev, I presume?
   );

   // submit_face_if_appropriate
   bool submit_face_if_appropriate(
      const std::size_t npart, const std::size_t iteration, const bool trim,
      const idx_vec &pcurr, // [ne]curr
      const idx_vec &pprev  // [ne]prev
   );

public:

   // ------------------------
   // constructor
   // ------------------------

   // helpers
   bool all_in_face(
      const iface &face,
      const iedge &edge
      );
   bool first_edge(
      const iface &face, const std::vector<idx_vec> &node_to_edge,
      idx_vec &f2e, const loop &n
      );
   bool next_edge_successive(
      const iface &face, const std::vector<idx_vec> &node_to_edge,
      idx_vec &f2e, const std::size_t n
      );
   void next_edge_worthwhile(
      const iface &face, const std::vector<idx_vec> &node_to_edge,
      idx_vec &f2e, const std::size_t n
      );

   // constructor
   explicit extrude_logic_23(
      const mesh<inode,iedge,iface,icell,ibase,2> &,
      /* */ mesh<onode,oedge,oface,ocell,obase,3> &,
      const PATH &,
      const NODE_ON &, const N2N &, const N2E &,
      const EDGE_ON &, const E2E &, const E2F &,
      const FACE_ON &, const F2F &, const F2C &
   );


   // ------------------------
   // callbacks
   // ------------------------

   // Parameters: (iteration,tie,trim,wrap)
   void layer_propose     (const std::size_t, const bool,const bool,const bool);
   void trim_vs_previous  (const std::size_t, const bool,const bool,const bool);
   void trim_vs_initial   (const std::size_t, const bool,const bool,const bool);
   void previous_eq_curr  (const std::size_t, const bool,const bool,const bool);
   void current_eq_initial(const std::size_t, const bool,const bool,const bool);

   // qqq Really need a more-compact system for these...
   void layer_submit(
      const std::size_t iteration,
      const typename is_node_else<face_terms,bool,char>::type,
      const typename is_node_else<cell_terms,bool,stub>::type,
      const typename is_node_else<cell_terms,bool,stub>::type);
   void layer_submit(
      const std::size_t iteration,
      const typename is_node_else<face_terms,bool,stub>::type,
      const typename is_edge_else<cell_terms,bool,char>::type,
      const typename is_edge_else<cell_terms,bool,stub>::type);
   void layer_submit(
      const std::size_t iteration,
      const typename is_node_else<face_terms,bool,stub>::type,
      const typename is_face_else<cell_terms,bool,stub>::type,
      const typename is_face_else<cell_terms,bool,char>::type);
   void layer_submit(
      const std::size_t iteration,
      const typename is_edge_else<face_terms,bool,char>::type,
      const typename is_node_else<cell_terms,bool,stub>::type,
      const typename is_node_else<cell_terms,bool,stub>::type);
   void layer_submit(
      const std::size_t iteration,
      const typename is_edge_else<face_terms,bool,stub>::type,
      const typename is_edge_else<cell_terms,bool,char>::type,
      const typename is_edge_else<cell_terms,bool,stub>::type);
   void layer_submit(
      const std::size_t iteration,
      const typename is_edge_else<face_terms,bool,stub>::type,
      const typename is_face_else<cell_terms,bool,stub>::type,
      const typename is_face_else<cell_terms,bool,char>::type);

   void filling_make(
      const std::size_t iteration,
      const typename is_node_else<face_terms,bool,char>::type,
      const typename is_node_else<cell_terms,bool,stub>::type,
      const typename is_node_else<cell_terms,bool,stub>::type);
   void filling_make(
      const std::size_t iteration,
      const typename is_node_else<face_terms,bool,stub>::type,
      const typename is_edge_else<cell_terms,bool,char>::type,
      const typename is_edge_else<cell_terms,bool,stub>::type);
   void filling_make(
      const std::size_t iteration,
      const typename is_node_else<face_terms,bool,stub>::type,
      const typename is_face_else<cell_terms,bool,stub>::type,
      const typename is_face_else<cell_terms,bool,char>::type);
   void filling_make(
      const std::size_t iteration,
      const typename is_edge_else<face_terms,bool,char>::type,
      const typename is_node_else<cell_terms,bool,stub>::type,
      const typename is_node_else<cell_terms,bool,stub>::type);
   void filling_make(
      const std::size_t iteration,
      const typename is_edge_else<face_terms,bool,stub>::type,
      const typename is_edge_else<cell_terms,bool,char>::type,
      const typename is_edge_else<cell_terms,bool,stub>::type);
   void filling_make(
      const std::size_t iteration,
      const typename is_edge_else<face_terms,bool,stub>::type,
      const typename is_face_else<cell_terms,bool,stub>::type,
      const typename is_face_else<cell_terms,bool,char>::type);
};



// =============================================================================
// Constructor: helper functions
// =============================================================================

// all_in_face
// All of the edge's vertices in the face?
extrude_logic_23_template
bool extrude_logic_23_type::all_in_face(
   const iface &face,
   const iedge &edge
) {
   const loop v(edge);
   while (v())
      if (!find(face,edge[v]))
         return false;
   return true;
}



// first_edge
extrude_logic_23_template
bool extrude_logic_23_type::first_edge(
   const iface &face, const std::vector<idx_vec> &node_to_edge,
   idx_vec &f2e, const loop &n
) {
   // for each node n of the face (until we find our first edge)
   while (n()) {
      // for each edge e of the node
      const loop e(node_to_edge[face[n]]);
      while (e())
         // if its vertices are ALL in the face, then bootstrap with this edge
         if (all_in_face(face, in.edge[node_to_edge[face[n]][e]]))
            return f2e.push_back(node_to_edge[face[n]][e]), true;
   }
   return false;  // no edges at all were found for this face
}



// next_edge_successive
extrude_logic_23_template
bool extrude_logic_23_type::next_edge_successive(
   const iface &face, const std::vector<idx_vec> &node_to_edge,
   idx_vec &f2e, const std::size_t n  // n = "next node" of the face
) {
   // for each edge e of the node
   const loop e(node_to_edge[face[n]]);
   while (e()) {
      if (find(f2e, node_to_edge[face[n]][e]))
         continue;  // already have this edge

      const iedge &edge = in.edge[node_to_edge[face[n]][e]];
      if (!all_in_face(face, edge))
         continue;  // this edge is not in the face

      // does this edge contain a vertex that was in the previous edge?
      const loop v(edge);
      while (v())
         if (find(in.edge[f2e.back()], edge[v]))
            return f2e.push_back(node_to_edge[face[n]][e]), true;
   }
   return false;  // no successive next edge
}



// next_edge_worthwhile
extrude_logic_23_template
void extrude_logic_23_type::next_edge_worthwhile(
   const iface &face, const std::vector<idx_vec> &node_to_edge,
   idx_vec &f2e, const std::size_t n  // n = "next node" of the face
) {
   // for each edge e of the node
   const loop e(node_to_edge[face[n]]);
   while (e())
      if (all_in_face(face, in.edge[node_to_edge[face[n]][e]]) &&
         !find(f2e, node_to_edge[face[n]][e]))
         f2e.push_back(node_to_edge[face[n]][e]);
}



// =============================================================================
// Constructor
// =============================================================================

extrude_logic_23_template
extrude_logic_23_type::extrude_logic_23(
   const mesh<inode,iedge,iface,icell,ibase,2> &i,
   /* */ mesh<onode,oedge,oface,ocell,obase,3> &o,
   const PATH &p,
   const NODE_ON &non, const N2N &n2n, const N2E &n2e,
   const EDGE_ON &eon, const E2E &e2e, const E2F &e2f,
   const FACE_ON &fon, const F2F &f2f, const F2C &f2c
) :
   extrude_info(
      i.node.size(),
      i.edge.size(),
      i.face.size(),
      // qqq Ordering of the following is screwy
      is_edge<face_terms>::value,
      is_edge<cell_terms>::value,
      is_face<cell_terms>::value,
      is_node<face_terms>::value,
      is_node<cell_terms>::value
   ),
   in(i), out(o), path(p),
   node_on(non), node2node(n2n), node2edge(n2e),
   edge_on(eon), edge2edge(e2e), edge2face(e2f),
   face_on(fon), face2face(f2f), face2cell(f2c),
   eps(get_eps<value_t>())
{
   // scaling is computed later

   // ================================
   // Compute f2e as overhead, in the
   // necessary cases
   // ================================

   if (is_node<face_terms>::value && !is_node<cell_terms>::value) {

      // pre-compute node-to-edge relationship
      std::vector<idx_vec> node_to_edge(nnode);
      while (e()) {
         const iedge &edge = in.edge[e];
         const loop n(edge);
         while (n())
            // drop edge e into its vertices' node_to_edges
            node_to_edge[edge[n]].push_back(e);
      }

      // compute f2e[f], for each face f
      while (f()) {
         bool successive = true;  // so far
         const loop n(in.face[f]);

         // over nodes n of face f, look for a (first) edge
         if (first_edge(in.face[f], node_to_edge, f2e[f], n))
            // continue with subsequent nodes n
            while (n()) {
               // look for an edge that touches the previous edge
               if (successive) {
                  if (next_edge_successive(in.face[f],node_to_edge,f2e[f],n))
                     continue;  // to the next node of the face

                  std::ostringstream oss;
                  oss << "Node ordering in node-based face [" << std::size_t(f)
                      << "] doesn't lead to successive edge\n   ordering. "
                         "I'll collect further edges, in no particular order";
                  note(oss,"");
                  successive = false;  // no longer
               }
               next_edge_worthwhile(in.face[f], node_to_edge, f2e[f], n);
            }
         else {
            std::ostringstream oss;
            oss << "Could find no edges around face ["
                << std::size_t(f) << "]. "
                   "Definitions of associated swept\n   edge-based cells will "
                   "involve only \"filling\" edges (from node extrusion)";
            warning(oss,"");
         }
      }
   }
}



// =============================================================================
// submit_edge_if_appropriate
// qqq Is this the same as the 1-2 case??? Offhand, it looks like it
// =============================================================================

extrude_logic_23_template
bool extrude_logic_23_type::submit_edge_if_appropriate(
   const std::size_t nnode, const std::size_t iteration, const bool trim
) {
   bool dup = trim && eprev[e];  const loop n(nnode);

   while (dup && n())  // avoid accessing output mesh, if possible...
      dup = ncurr[in.edge[e][n]] == nprev[in.edge[e][n]];

   if (dup) {  // oh well
      n.reset();
      while (dup && n())
         dup = ncurr[in.edge[e][n]]-1 == prev_edge(e)[n];
   }

#ifdef METAMESH_ASSERT
   // old scheme; be sure new one (above) is equivalent
   bool dup2 = trim && eprev[e];  n.reset();
   while (dup2 && n())
      dup2 = ncurr[in.edge[e][n]]-1 == prev_edge(e)[n];
   assert(dup2 == dup);
#endif

   if (!dup) {
      oedge E;  E.clear(nnode);  n.reset();
      while (n())
         E.push(ncurr[in.edge[e][n]]-1, std::size_t(n));

      metamesh_form2form(e,edge, edge2edge, oedge,E);
      book(out.edge, ecurr, einit, e);
   }

   return !dup;
}



// =============================================================================
// submit_face_if_appropriate
// =============================================================================

// qqq Eventually, evaluate any meaningful difference between part == node and
// part == edge cases, and also, evaluate whether or not this function and the
// above one could be made into a single, perhaps templated function.

// note: "part" can be node or edge
extrude_logic_23_template
bool extrude_logic_23_type::submit_face_if_appropriate(
   const std::size_t npart, const std::size_t iteration, const bool trim,
   const idx_vec &pcurr, // [ne]curr
   const idx_vec &pprev  // [ne]prev
) {
   bool dup = trim && fprev[f];  const loop p(npart);

   while (dup && p())  // avoid accessing output mesh, if possible...
      dup = pcurr[in.face[f][p]] == pprev[in.face[f][p]];

   if (dup) {  // oh well
      p.reset();
      while (dup && p())
         dup = pcurr[in.face[f][p]]-1 == prev_face(f)[p];
   }

#ifdef METAMESH_ASSERT
   // old scheme; be sure new one (above) is equivalent
   bool dup2 = trim && fprev[f];  p.reset();
   while (dup2 && p())
      dup2 = pcurr[in.face[f][p]]-1 == prev_face(f)[p];
   assert(dup2 == dup);
#endif

   if (!dup) {
      oface F;  F.clear(npart);  p.reset();
      while (p())
         F.push(pcurr[in.face[f][p]]-1, std::size_t(p));

      metamesh_form2form(f,face, face2face, oface,F);
      book(out.face, fcurr, finit, f);
   }

   return !dup;
}



// =============================================================================
// layer_propose
// layer_submit
// =============================================================================

// layer_propose
extrude_logic_23_function(layer_propose)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   // Nodes
   while (n()) {
      // Propagate base, then coordinate. See remark in extrude01 file.
      if ((void *)&node2node != (void *)&metamesh::noop)
      node2node.
      node2node(in,out,iteration,std::size_t(n),in.node[n],proposed[n]);
      path.
      path     (in,out,iteration,std::size_t(n),in.node[n],proposed[n]);

      nodeison[n] =
      node_on.
      node_on  (in,out,iteration,std::size_t(n),in.node[n],proposed);
   }

   // Edges
   while (e())
      edgeison[e] =
      edge_on.
      edge_on  (in,out, iteration,std::size_t(e), in.edge[e],proposed);

   // Faces
   std::vector<bool> &ison = is_node<face_terms>::value ? nodeison : edgeison;
   while (f()) {
      faceison[f] =
      face_on.
      face_on  (in,out, iteration,std::size_t(f), in.face[f],proposed);

      if (faceison[f]) {  // then go back and ensure we have its nodes/edges...
         const loop v(in.face[f]);
         while (v())
            ison[in.face[f][v]] = true;

         // For the following cases:
         //    face<node>, cell<edge>
         //    face<node>, cell<face>
         // we must switch-on any edges that are associated (indirectly, here)
         // with "on" faces. In the former case this is because the cells (which
         // are created by face extrusion) need these edges directly, for their
         // definitions. In the latter case this is because the cell definitions
         // need not only the bounding faces, but also the filling-faces that
         // are created by the extrude actions of the edges associated with the
         // bounding faces---edges which therefore must be "on."
         if (is_node<face_terms>::value && !is_node<cell_terms>::value) {
            const loop e(f2e[f]);
            while (e())
               edgeison[f2e[f][e]] = true;
         }
      }
   }

   // Always needed; is here in case edgeison was modified due to face<edge>
   while (e())
      if (edgeison[e]) {  // then go back and ensure we have its nodes...
         const loop n(in.edge[e]);
         while (n())
            nodeison[in.edge[e][n]] = true;
      }

   // qqq Is the following crap exactly the same for 0-1, 1-2, and 2-3 cases???
   // Determine length scaling. We do this after looking at edges and faces (not
   // just after looking at nodes), because nodeison[] may be modified there.
   if (trim) {
      scaling = 0;
      std::size_t num = 0;

      while (n())
         if (nodeison[n] && nprev[n]) {
            const value_t d = distance(proposed[n], prev_node(n));
            if (d != value_t(0))  // exclude stationary nodes
               num++, scaling += d;
         }
      scaling = num ? scaling/num : 1;  // average of nonzero node movements
   }
}



// layer_submit
// If output face<node> and cell<node>: see metamesh-fnode-cnode.h
// If output face<node> and cell<edge>: see metamesh-fnode-cedge.h
// If output face<node> and cell<face>: see metamesh-fnode-cface.h
// If output face<edge> and cell<node>: see metamesh-fedge-cnode.h
// If output face<edge> and cell<edge>: see metamesh-fedge-cedge.h
// If output face<edge> and cell<face>: see metamesh-fedge-cface.h



// =============================================================================
// trim_vs_previous
// trim_vs_initial
// qqq Are these exactly the same as for 0-1 and 1-2 extrusions?
// =============================================================================

// trim_vs_previous
extrude_logic_23_function(trim_vs_previous)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   while (n())
      if (nodeison[n] && nprev[n] &&
          near(proposed[n], prev_node(n), scaling,eps)) {
         nodeison[n] = false;  // duplicate of previous; turn back off

         // See remark in extrude01 file.
         assert(ncurr[n] == nprev[n]);  // take out sometime
      }
}



// trim_vs_initial
extrude_logic_23_function(trim_vs_initial)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   while (n())
      if (nodeison[n] && ninit[n] &&
          near(proposed[n], init_node(n), scaling,eps)) {
         nodeison[n] = false;  // duplicate of initial; turn back off

         // See remark in extrude01 file.
         ncurr[n] = ninit[n];
      }
}



// =============================================================================
// filling_make
// =============================================================================

// filling_make
// If output face<node> and cell<node>: see metamesh-fnode-cnode.h
// If output face<node> and cell<edge>: see metamesh-fnode-cedge.h
// If output face<node> and cell<face>: see metamesh-fnode-cface.h
// If output face<edge> and cell<node>: see metamesh-fedge-cnode.h
// If output face<edge> and cell<edge>: see metamesh-fedge-cedge.h
// If output face<edge> and cell<face>: see metamesh-fedge-cface.h



// =============================================================================
// previous_eq_curr
// current_eq_initial
// qqq Almost the same as edge cases; just have face assignments too
// =============================================================================

// previous_eq_curr
extrude_logic_23_function(previous_eq_curr)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;
   nprev = ncurr;
   eprev = ecurr;
   fprev = fcurr;
}

// current_eq_initial
extrude_logic_23_function(current_eq_initial)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;
   ncurr = ninit;
   ecurr = einit;
   fcurr = finit;
}



// =============================================================================
// extrude23
//    in, path, more, node_on, edge_on, face_on, out, tying, trimming,
//    action,
//    node2node, node2edge,
//    edge2edge, edge2face,
//    face2face, face2cell
// =============================================================================

template<
   class inode, class iedge, class iface, class icell, class ibase,
   class onode, class oedge, class oface, class ocell, class obase,
   class PATH, class MORE, class ACTION,
   class NODE_ON, class N2N, class N2E,
   class EDGE_ON, class E2E, class E2F,
   class FACE_ON, class F2F, class F2C
>
mesh<onode,oedge,oface,ocell,obase,3> &extrude23(
   // extrude_info pointer
   const extrude_info<
      metamesh::mesh<inode,iedge,iface,icell,ibase,2>,
      metamesh::mesh<onode,oedge,oface,ocell,obase,3>,
      3
   > * &ptr,

   // input mesh
   const mesh<inode,iedge,iface,icell,ibase,2> &in,

   // extrusion path, continuation condition
   const PATH &path,
   const MORE &more,

   // masking
   const NODE_ON &node_on,
   const EDGE_ON &edge_on,
   const FACE_ON &face_on,

   // output mesh
   mesh<onode,oedge,oface,ocell,obase,3> &out,

   // tie and trim flags
   const tie_t  tying,
   const trim_t trimming,

   // miscellaneous functors
   const ACTION &action,
   const N2N &node2node, const N2E &node2edge,
   const E2E &edge2edge, const E2F &edge2face,
   const F2F &face2face, const F2C &face2cell
) {
   // Prefix: clear output mesh, check input mesh
   if (!extrude_prefix(in,out))
      return out;

   // Extrude-logic callback object
   extrude_logic_23_type plugins(
      in, out, path,
      node_on, node2node, node2edge,
      edge_on, edge2edge, edge2face,
      face_on, face2face, face2cell
   );

   // Extrusion
   ptr = &plugins;
   extrude_logic(in, out, more, action, plugins, tying, trimming);
   ptr = nullptr;

   // Suffix: check output mesh
   return extrude_suffix(out);
}

}  // internal
}  // metamesh

// We don't #undef the macros quite yet, as they're used elsewhere

#endif
