/* -*- C++ -*- */

#ifndef METAMESH_FNODE_CFACE
#define METAMESH_FNODE_CFACE

// For the
//    face<node>, cell<face>
// extrude 2-3 variant, this file provides layer_submit() and filling_make().

namespace metamesh {
namespace internal {



// =============================================================================
// layer_submit
// =============================================================================

extrude_logic_23_template
void extrude_logic_23_type::layer_submit(
   const std::size_t iteration,
   const typename is_node_else<face_terms,bool,stub>::type tie,
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
   while (e()) {
      const std::size_t nnode = in.edge[e].size();
      const loop n(nnode);
      idx_vec_pair &fsides = eprev[e] ? e2fsides[e] : e2fbegin[e];

      const std::size_t a = nnode ? in.edge[e][n.min()] : 0;
      const std::size_t b = nnode ? in.edge[e][n.max()] : 0;

      if (!edgeison[e]) {
         if (nnode && nodeison[a]) fsides.first .push_back(ncurr[a]);
         if (nnode && nodeison[b]) fsides.second.push_back(ncurr[b]);
      } else if (submit_edge_if_appropriate(nnode,iteration,trim) && nnode) {
         if (fsides.first .size() && fsides.first .back() == ncurr[a])
             fsides.first .pop_back();
         if (fsides.second.size() && fsides.second.back() == ncurr[b])
             fsides.second.pop_back();
      }
   }

   // Faces
   while (f())
      if (faceison[f])
         submit_face_if_appropriate
            (in.face[f].size(),iteration,trim,ncurr,nprev);
}



// =============================================================================
// filling_make
// =============================================================================

extrude_logic_23_template
void extrude_logic_23_type::filling_make(
   const std::size_t iteration,
   const typename is_node_else<face_terms,bool,stub>::type tie,
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
      }

   // Edges to faces
   while (e())
      if (changed(eprev, ecurr, e)) {
         const std::size_t nnode = in.edge[e].size();
         const loop n(nnode);

         // initialize face
         std::size_t want = nnode
            +         e2fsides[e].second.size()
            + (wrap ? e2fbegin[e].second.size() : 0)
            + (wrap ? e2fbegin[e].first .size() : 0)
            +         e2fsides[e].first .size();
         /**/
         while (n()) {
            /*
            if (curr_edge(e)[n] != ncurr[in.edge[e][n]]-1) {
               // 7053 versus 1  :-/
               std::cout << "edge #" << std::size_t(e) << std::endl;
               std::cout << "vert #" << std::size_t(n) << std::endl;
               std::cout << "curr_edge(e)[n]        = "
                         << (curr_edge(e)[n]       ) << std::endl;
               std::cout << "ncurr[in.edge[e][n]]-1 = "
                         << (ncurr[in.edge[e][n]]-1) << std::endl;
               std::cout << "prev_edge(e)[n]        = "
                         << (prev_edge(e)[n]       ) << std::endl;
            }
            assert(curr_edge(e)[n] == ncurr[in.edge[e][n]]-1);
            */

            /*
            if (ncurr[in.edge[e][n]] != nprev[in.edge[e][n]])
               want++;
            else {
            }
            */

            /*
            std::cout
               << (ncurr[in.edge[e][n]] == nprev[in.edge[e][n]] ? 't' : 'f')
               << (curr_edge(e)[n]      == prev_edge(e)[n]      ? 't' : 'f')
               << std::endl;
            */

            if (ncurr[in.edge[e][n]] != nprev[in.edge[e][n]])  // implies...
               assert(curr_edge(e)[n] != prev_edge(e)[n]);
            /**/

            want += curr_edge(e)[n] != prev_edge(e)[n];
         }
         /**/
         /*
         while (n())
            want += curr_edge(e)[n] != prev_edge(e)[n];
         */

         std::size_t count = 0;  oface F;  F.clear(want);

         // lower forward
         while (n())
            F.push(prev_edge(e)[n], count++);

         // right, right initial
         forward(F, e2fsides[e].second, count);
         forward(F, e2fbegin[e].second, count,wrap);

         // upper reverse
         while (n.back())
            if (curr_edge(e)[n] != prev_edge(e)[n])
               F.push(curr_edge(e)[n], count++);

         // left initial, left
         reverse(F, e2fbegin[e].first,  count,wrap);
         reverse(F, e2fsides[e].first,  count);

         // base
         metamesh_form2form(e,edge, edge2face, oface,F);
         e2f[e] = out.face.size();  // edge to associated filling face
      }

   // Faces to cells
   while (f()) {
      idx_vec &csides = fprev[f] ? f2csides[f] : f2cbegin[f];
      const loop e(f2e[f]);
      while (e()) {
         const std::size_t eindex = f2e[f][e];
         if (changed(eprev,ecurr,eindex))
            csides.push_back(e2f[eindex]);
      }

      if (changed(fprev, fcurr, f)) {
         // initialize cell
         ocell C;  std::size_t count = 0;
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

#endif
