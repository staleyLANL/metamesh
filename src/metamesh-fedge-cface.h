/* -*- C++ -*- */

#ifndef METAMESH_FEDGE_CFACE
#define METAMESH_FEDGE_CFACE

// For the
//    face<edge>, cell<face>
// extrude 2-3 variant, this file provides layer_submit() and filling_make().

namespace metamesh {
namespace internal {



// =============================================================================
// layer_submit
// =============================================================================

extrude_logic_23_template
void extrude_logic_23_type::layer_submit(
   const std::size_t iteration,
   const typename is_edge_else<face_terms,bool,stub>::type tie,
   const typename is_face_else<cell_terms,bool,stub>::type trim,
   const typename is_face_else<cell_terms,bool,char>::type wrap
) {
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   // Nodes
   while (n())
      if (nodeison[n]) {
         out.push(proposed[n]);
         book(out.node, ncurr, ninit, n);
      }

   // Edges
   while (e())
      if (edgeison[e])
         submit_edge_if_appropriate(in.edge[e].size(),iteration,trim);

   // Faces
   while (f())
      if (faceison[f])
         submit_face_if_appropriate
            (in.face[f].size(),iteration,trim,ecurr,eprev);
}



// =============================================================================
// filling_make
// =============================================================================

extrude_logic_23_template
void extrude_logic_23_type::filling_make(
   const std::size_t iteration,
   const typename is_edge_else<face_terms,bool,stub>::type tie,
   const typename is_face_else<cell_terms,bool,stub>::type trim,
   const typename is_face_else<cell_terms,bool,char>::type wrap
) {
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   // Nodes to edges
   while (n())
      if (changed(nprev, ncurr, n)) {
         oedge E;  E.clear(2);
         E.push(nprev[n]-1, 0);
         E.push(ncurr[n]-1, 1);

         metamesh_form2form(n,node, node2edge, oedge,E);
         n2e[n] = out.edge.size();  // node to associated filling edge
      }

   // Edges to faces
   while (e()) {
      const std::size_t nnode = in.edge[e].size();
      const loop n(nnode);
      idx_vec_pair &fsides = eprev[e] ? e2fsides[e] : e2fbegin[e];

      const std::size_t a = nnode ? in.edge[e][n.min()] : 0;
      if (nnode && changed(nprev, ncurr, a)) fsides.first .push_back(n2e[a]);
      const std::size_t b = nnode ? in.edge[e][n.max()] : 0;
      if (nnode && changed(nprev, ncurr, b)) fsides.second.push_back(n2e[b]);

      if (changed(eprev, ecurr, e)) {
         std::size_t count = 0;  oface F;  F.clear(
               2 +    e2fsides[e].second.size()
            + (wrap ? e2fbegin[e].second.size() : 0)
            + (wrap ? e2fbegin[e].first .size() : 0)
            +         e2fsides[e].first .size()
         );

         F.push(eprev[e]-1, count++);  // lower
         forward(F, e2fsides[e].second, count); // right
         forward(F, e2fbegin[e].second, count,wrap); // right initial
         F.push(ecurr[e]-1, count++);  // upper
         reverse(F, e2fbegin[e].first,  count,wrap); // left  initial
         reverse(F, e2fsides[e].first,  count); // left

         // base
         metamesh_form2form(e,edge, edge2face, oface,F);
         e2f[e] = out.face.size();  // edge to associated filling face
      }
   }

   // Faces to cells
   while (f()) {
      const std::size_t nedge = in.face[f].size();
      const loop e(nedge);
      idx_vec &csides = fprev[f] ? f2csides[f] : f2cbegin[f];

      while (e()) {
         const std::size_t eindex = in.face[f][e];
         if (changed(eprev,ecurr,eindex) && !find(csides,e2f[eindex]))
            csides.push_back(e2f[eindex]);
      }

      if (changed(fprev, fcurr, f)) {
         // initialize cell
         std::size_t count = 0;  ocell C;
         C.clear(2 + f2csides[f].size() + (wrap ? f2cbegin[f].size() : 0));

         // begin
         C.push(fprev[f]-1, count++);

         // inner, inner initial
         forward(C, f2csides[f], count);
         forward(C, f2cbegin[f], count,wrap);

         // end
         C.push(fcurr[f]-1, count++);

         // base
         metamesh_form2form(f,face, face2cell, ocell,C);
      }
   }
}

}  // internal
}  // metamesh

// Macros: undefine; no longer need
#undef extrude_logic_23_template
#undef extrude_logic_23_type
#undef extrude_logic_23_function

#endif
