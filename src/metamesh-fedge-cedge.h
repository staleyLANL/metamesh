/* -*- C++ -*- */

#ifndef METAMESH_FEDGE_CEDGE
#define METAMESH_FEDGE_CEDGE

// For the
//    face<edge>, cell<edge>
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
   const typename is_edge_else<cell_terms,bool,char>::type trim,
   const typename is_edge_else<cell_terms,bool,stub>::type wrap
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
   while (f()) {
      const std::size_t nedge = in.face[f].size();
      const loop e(nedge);
      idx_vec &csides = fprev[f] ? f2csides[f] : f2cbegin[f];

      if (!faceison[f])
         while (e()) {
            const std::size_t eindex = in.face[f][e];
            if (edgeison[eindex] && !find(csides, ecurr[eindex]))
               csides.push_back(ecurr[eindex]);
         }
      else if (submit_face_if_appropriate(nedge,iteration,trim,ecurr,eprev))
         while (e()) {
            const std::size_t eindex = in.face[f][e];
            const std::vector<std::size_t>::iterator found =
               std::find(csides.begin(), csides.end(), ecurr[eindex]);
            if (found != csides.end())  // already there
               csides.erase(found);
         }
   }
}



// =============================================================================
// filling_make
// =============================================================================

extrude_logic_23_template
void extrude_logic_23_type::filling_make(
   const std::size_t iteration,
   const typename is_edge_else<face_terms,bool,stub>::type tie,
   const typename is_edge_else<cell_terms,bool,char>::type trim,
   const typename is_edge_else<cell_terms,bool,stub>::type wrap
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
      }
   }

   // Faces to cells
   while (f()) {
      const std::size_t nedge = in.face[f].size();
      const loop e(nedge);
      idx_vec &csides = fprev[f] ? f2csides[f] : f2cbegin[f];

      while (e()) {
         const std::size_t eindex = in.face[f][e];
         const loop n(in.edge[eindex]);
         while (n()) {
            const std::size_t nindex = in.edge[eindex][n];
            if (changed(nprev,ncurr,nindex) && !find(csides,n2e[nindex]))
               csides.push_back(n2e[nindex]);
         }
      }

      if (changed(fprev, fcurr, f)) {
         // initialize cell
         std::size_t want = nedge + f2csides[f].size();
         if (wrap) want += f2cbegin[f].size();
         while (e())
            want += curr_face(f)[e] != prev_face(f)[e];
         std::size_t count = 0;  ocell C;  C.clear(want);

         // lower forward
         while (e())
            C.push(prev_face(f)[e], count++);

         // inner, inner initial
         forward(C, f2csides[f], count);
         forward(C, f2cbegin[f], count,wrap);

         // upper forward (not reverse)
         while (e())
            if (curr_face(f)[e] != prev_face(f)[e])
               C.push(curr_face(f)[e], count++);

         // base
         metamesh_form2form(f,face, face2cell, ocell,C);
      }
   }
}

}  // internal
}  // metamesh

#endif
