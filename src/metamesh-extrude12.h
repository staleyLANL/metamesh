/* -*- C++ -*- */

#ifndef METAMESH_EXTRUDE12
#define METAMESH_EXTRUDE12

/*

This file provides functionality for 1-form to 2-form extrusions.

Variants:

mesh<node,edge<node>> to mesh<node,edge<node>,face<node>>

   layer:   node       to node
   filling: node       to edge<node>
   layer:   edge<node> to edge<node>
   filling: edge<node> to face<node>

mesh<node,edge<node>> to mesh<node,edge<node>,face<edge>>

   layer:   node       to node
   filling: node       to edge<node>
   layer:   edge<node> to edge<node>
   filling: edge<node> to face<edge>

*/

// Whole file
namespace metamesh {
namespace internal {



// =============================================================================
// extrude_info: 1-to-2
// =============================================================================

// 2 = output form
template<class IMESH, class OMESH>
class extrude_info<IMESH,OMESH,2> {

   using onode = typename OMESH::node_t;

public:

   // ------------------------
   // data
   // ------------------------

   // number of nodes/edges in input mesh; loopers
   const std::size_t nnode;  const loop n;
   const std::size_t nedge;  const loop e;

   // node index+1's in output mesh; 0 = uninitialized
   // edge index+1's in output mesh; 0 = uninitialized
   std::vector<std::size_t>
      ncurr, nprev, ninit,
      ecurr, eprev, einit;

   // proposed new layer
   std::vector<onode> proposed;  // nodes themselves
   std::vector< bool> nodeison;  // nodes on/true?
   std::vector< bool> edgeison;  // edges on/true?

   // qqq...
   // Need better comments on n2e, e2fsides, e2fbegin ...
   // Exactly what filling? relative to init, prev, curr?
   std::vector<std::size_t>
      n2e;  // for each input node, mesh.edge index of its filling edge

   std::vector<
      std::pair<std::vector<std::size_t>,std::vector<std::size_t>>
   > e2fsides, e2fbegin;  // #=nedge, swept to faces


   // ------------------------
   // constructor
   // ------------------------

   explicit extrude_info(
      const std::size_t _nnode,
      const std::size_t _nedge,
      const bool face_terms_is_edge
   ) :
      nnode(_nnode), n(nnode),
      nedge(_nedge), e(nedge),

      ncurr(nnode,0), nprev(nnode,0), ninit(nnode,0),
      ecurr(nedge,0), eprev(nedge,0), einit(nedge,0),

      proposed(nnode),
      nodeison(nnode),
      edgeison(nedge),

      // For each node, n2e gives the latest filling edges, which we need
      // in order to build faces from edges. Used iff output face<edge>.
      n2e(face_terms_is_edge ? nnode : 0, 0),

      // For each input edge, e2fsides collects up either the side-nodes
      // or side-edges that will be part of the edge's eventual swept face.
      e2fsides(nedge), e2fbegin(nedge)
   { }
};



// =============================================================================
// Macros
// =============================================================================

// extrude_logic_12_template
#define extrude_logic_12_template\
   template<\
      class inode, class iedge, class iface, class icell, class ibase,\
      class onode, class oedge, class oface, class ocell, class obase,\
      class PATH,\
      class NODE_ON, class N2N, class N2E,\
      class EDGE_ON, class E2E, class E2F\
   >

// extrude_logic_12_type
#define extrude_logic_12_type\
   extrude_logic_12<\
      inode, iedge, iface, icell, ibase,\
      onode, oedge, oface, ocell, obase,\
      PATH,\
      NODE_ON, N2N, N2E,\
      EDGE_ON, E2E, E2F\
   >

// extrude_logic_12_function(fun)
#define extrude_logic_12_function(fun)\
   extrude_logic_12_template\
   void extrude_logic_12_type::fun(\
      const std::size_t iteration,\
      const bool tie, const bool trim, const bool wrap\
   )



// =============================================================================
// extrude_logic_12
// Function object; an instance is sent to the general extrude_logic()
// =============================================================================

extrude_logic_12_template
class extrude_logic_12 :
   public internal::extrude_info<
      metamesh::mesh<inode,iedge,iface,icell,ibase,1>,
      metamesh::mesh<onode,oedge,oface,ocell,obase,2>,
      2
   >
{
public:

   using extrude_info = internal::extrude_info<
      metamesh::mesh<inode,iedge,iface,icell,ibase,1>,
      metamesh::mesh<onode,oedge,oface,ocell,obase,2>, 2
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

private:

   // types
   using value_t      = typename onode::value_t;  // output node value_t
   using idx_vec      = std::vector<std::size_t>;
   using idx_vec_pair = std::pair<idx_vec,idx_vec>;
   using face_terms   = typename oface::basis_t;  // node | edge

   // meshes
   const mesh<inode,iedge,iface,icell,ibase,1> &in;
   /* */ mesh<onode,oedge,oface,ocell,obase,2> &out;

   // functors
   const PATH &path;
   const NODE_ON &node_on;  const N2N &node2node;  const N2E &node2edge;
   const EDGE_ON &edge_on;  const E2E &edge2edge;  const E2F &edge2face;

   // eps, length scaling
   const value_t eps;  value_t scaling;

   // for convenience
   // qqq no curr_node? no init_edge?
   inline const onode &init_node(const std::size_t n) const
      { return out.node[ninit[n]-1]; }
   inline const onode &prev_node(const std::size_t n) const
      { return out.node[nprev[n]-1]; }

   inline const oedge &prev_edge(const std::size_t e) const
      { return out.edge[eprev[e]-1]; }
   inline const oedge &curr_edge(const std::size_t e) const
      { return out.edge[ecurr[e]-1]; }

   // submit_edge_if_appropriate
   bool submit_edge_if_appropriate
      (const std::size_t, const std::size_t, const bool);

public:

   // constructor
   explicit extrude_logic_12(
      const mesh<inode,iedge,iface,icell,ibase,1> &,
      /* */ mesh<onode,oedge,oface,ocell,obase,2> &,
      const PATH &,
      const NODE_ON &, const N2N &, const N2E &,
      const EDGE_ON &, const E2E &, const E2F &
   );

   // callbacks
   // Parameters: (iteration,tie,trim,wrap)
   void layer_propose     (const std::size_t, const bool,const bool,const bool);
   void trim_vs_previous  (const std::size_t, const bool,const bool,const bool);
   void trim_vs_initial   (const std::size_t, const bool,const bool,const bool);
   void previous_eq_curr  (const std::size_t, const bool,const bool,const bool);
   void current_eq_initial(const std::size_t, const bool,const bool,const bool);

   void layer_submit(  // for output face<node>
      const typename is_node_else<face_terms,std::size_t,stub>::type,
      const bool, const bool, const bool);
   void layer_submit(  // for output face<edge>
      const typename is_edge_else<face_terms,std::size_t,stub>::type,
      const bool, const bool, const bool);

   void filling_make(  // for output face<node>
      const typename is_node_else<face_terms,std::size_t,stub>::type,
      const bool, const bool, const bool);
   void filling_make(  // for output face<edge>
      const typename is_edge_else<face_terms,std::size_t,stub>::type,
      const bool, const bool, const bool);
};



// =============================================================================
// Constructor
// =============================================================================

extrude_logic_12_template
extrude_logic_12_type::extrude_logic_12(
   const mesh<inode,iedge,iface,icell,ibase,1> &i,
   /* */ mesh<onode,oedge,oface,ocell,obase,2> &o,
   const PATH &p,
   const NODE_ON &non, const N2N &n2n, const N2E &n2e,
   const EDGE_ON &eon, const E2E &e2e, const E2F &e2f
) :
   extrude_info(
     i.node.size(),
     i.edge.size(),
     is_edge<face_terms>::value
   ),
   in(i), out(o), path(p),
   node_on(non), node2node(n2n), node2edge(n2e),
   edge_on(eon), edge2edge(e2e), edge2face(e2f),
   eps(get_eps<value_t>())
{
   // scaling is computed later
}



// =============================================================================
// submit_edge_if_appropriate
// Submit layer edge, subject to certain conditions
// =============================================================================

extrude_logic_12_template
bool extrude_logic_12_type::submit_edge_if_appropriate(
   const std::size_t nnode, const std::size_t iteration, const bool trim
) {
   // Submit the edge, as long as we don't have a situation where we're
   // trimming, there's a previous edge, and the edge-to-be would equal
   // the previous edge. In other words, submit if it's not an unwanted
   // duplicate. Note that we can't just consider edge e's nodes for this
   // test. Even if all of nodes are identical to their previous values,
   // it's possible (if edgeison was false before) that no previous edge
   // was drawn through them. The following test is correct.

   // Necessary condition to be an unwanted duplicate: must be unwanted
   // (because we're trimming), and must have a previous value against
   // which to compare.
   bool dup = trim && eprev[e];

   // Now make condition sufficient: each node index that the new edge
   // would get must equal what it was for the previous edge.
   const loop n(nnode);

   while (dup && n())  // avoid accessing output mesh, if possible
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
// layer_propose
// layer_submit
// =============================================================================

// layer_propose
extrude_logic_12_function(layer_propose)
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
   // qqq Is this block the only thing in addition to the 0-1 case?
   while (e()) {
      edgeison[e] =
      edge_on.
      edge_on  (in,out, iteration,std::size_t(e), in.edge[e],proposed);

      if (edgeison[e]) {  // then go back and ensure we have its nodes...
         const loop n(in.edge[e]);
         while (n())
            nodeison[in.edge[e][n]] = true;

         // Note: even if forced-on here, nodes that prove to be unwanted
         // duplicates are still forced-off later
      }
   }

   // Determine length scaling. We do this after looking at edges (not just
   // after looking at nodes), because nodeison[] may be modified there.
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
// If output face<node>: see metamesh-fnode.h
// If output face<edge>: see metamesh-fedge.h



// =============================================================================
// trim_vs_previous
// trim_vs_initial
// qqq Are these exactly the same as for 0-1 extrusion?
// =============================================================================

// trim_vs_previous
extrude_logic_12_function(trim_vs_previous)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   while (n())
      if (nodeison[n] && nprev[n] &&
          near(proposed[n], prev_node(n), scaling,eps)) {
         nodeison[n] = false;  // duplicate of previous; turn back off

         // See remark in extrude01 file
         assert(ncurr[n] == nprev[n]);  // take out sometime
      }
}



// trim_vs_initial
extrude_logic_12_function(trim_vs_initial)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   while (n())
      if (nodeison[n] && ninit[n] &&
          near(proposed[n], init_node(n), scaling,eps)) {
         nodeison[n] = false;  // duplicate of initial; turn back off

         // See remark in extrude01 file
         ncurr[n] = ninit[n];
      }
}



// =============================================================================
// filling_make
// =============================================================================

// filling_make
// If output faces are based on nodes: see metamesh-fnode.h
// If output faces are based on edges: see metamesh-fedge.h



// =============================================================================
// previous_eq_curr
// current_eq_initial
// qqq Almost the same as node cases; just have edge assignments too
// =============================================================================

// previous_eq_curr
extrude_logic_12_function(previous_eq_curr)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;
   nprev = ncurr;
   eprev = ecurr;
}

// current_eq_initial
extrude_logic_12_function(current_eq_initial)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;
   ncurr = ninit;
   ecurr = einit;
}



// =============================================================================
// extrude12
//    in, path, more, node_on, edge_on, out, tying, trimming,
//    action,
//    node2node, node2edge,
//    edge2edge, edge2face
// =============================================================================

template<
   class inode, class iedge, class iface, class icell, class ibase,
   class onode, class oedge, class oface, class ocell, class obase,
   class PATH, class MORE,  class ACTION,
   class NODE_ON, class N2N, class N2E,
   class EDGE_ON, class E2E, class E2F
>
mesh<onode,oedge,oface,ocell,obase,2> &extrude12(
   // extrude_info pointer
   const extrude_info<
      metamesh::mesh<inode,iedge,iface,icell,ibase,1>,
      metamesh::mesh<onode,oedge,oface,ocell,obase,2>,
      2
   > * &ptr,

   // input mesh
   const mesh<inode,iedge,iface,icell,ibase,1> &in,

   // extrusion path, continuation condition
   const PATH &path,
   const MORE &more,

   // masking
   const NODE_ON &node_on,
   const EDGE_ON &edge_on,

   // output mesh
   mesh<onode,oedge,oface,ocell,obase,2> &out,

   // tie and trim flags
   const tie_t  tying,
   const trim_t trimming,

   // miscellaneous functors
   const ACTION &action,
   const N2N &node2node, const N2E &node2edge,
   const E2E &edge2edge, const E2F &edge2face
) {
   // Prefix: clear output mesh, check input mesh
   if (!extrude_prefix(in,out))
      return out;

   // Extrude-logic callback object
   extrude_logic_12_type plugins(
      in, out, path,
      node_on, node2node, node2edge,
      edge_on, edge2edge, edge2face
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
