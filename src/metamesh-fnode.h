/* -*- C++ -*- */

#ifndef METAMESH_FNODE
#define METAMESH_FNODE

// For the
//    face<node>
// extrude 1-2 variant, this file provides layer_submit() and filling_make().

// Whole file
namespace metamesh {
namespace internal {



// =============================================================================
// layer_submit
// =============================================================================

extrude_logic_12_template
void extrude_logic_12_type::layer_submit(
   const typename is_node_else<face_terms,std::size_t,stub>::type iteration,
   const bool tie, const bool trim, const bool wrap
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

      // node-vector indices for edge e's end nodes; often 0 and 1
      const std::size_t a = nnode ? in.edge[e][n.min()] : 0;
      const std::size_t b = nnode ? in.edge[e][n.max()] : 0;

      if (edgeison[e]) {
         if (submit_edge_if_appropriate(nnode,iteration,trim) && nnode) {
            // Remove previously-buffered face-nodes that now prove to be used
            // in this later face-closing edge. This amounts to back-trimming
            // fsides, now that we have the information necessary to do so.
            if (fsides.first .size() && fsides.first .back() == ncurr[a])
                fsides.first .pop_back();
            if (fsides.second.size() && fsides.second.back() == ncurr[b])
                fsides.second.pop_back();
         }
      } else if (nnode) {
         //  Buffer any fully-on nodes, for later use in swept face
         if (nodeison[a]) fsides.first .push_back(ncurr[a]);
         if (nodeison[b]) fsides.second.push_back(ncurr[b]);
      }
   }
}



// =============================================================================
// filling_make
// =============================================================================

extrude_logic_12_template
void extrude_logic_12_type::filling_make(
   const typename is_node_else<face_terms,std::size_t,stub>::type iteration,
   const bool tie, const bool trim, const bool wrap
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

         // Initialize face
         std::size_t want = nnode
            +         e2fsides[e].second.size()
            + (wrap ? e2fbegin[e].second.size() : 0)
            + (wrap ? e2fbegin[e].first .size() : 0)
            +         e2fsides[e].first .size();
         while (n())
            want += curr_edge(e)[n] != prev_edge(e)[n];

#ifdef METAMESH_ASSERT
         // qqq can a state-array version be made equivalent?
         //     note: in any event, also need to consider later code...
         //     in this filling_make() function; also uses curr and prev _edge
         int aaa = 0;
         int bbb = 0;
         while (n()) {
            aaa = ncurr[in.edge[e][n]] != nprev[in.edge[e][n]];
            bbb = curr_edge(e)[n] != prev_edge(e)[n];
         }
         assert(aaa = bbb);
#endif

         std::size_t count = 0;  oface F;  F.clear(want);

         // lower forward
         while (n())
            F.push(prev_edge(e)[n], count++);

         forward(F, e2fsides[e].second, count); // r
         forward(F, e2fbegin[e].second, count,wrap); // r initial

         // upper reverse
         while (n.back())
            if (curr_edge(e)[n] != prev_edge(e)[n])
               F.push(curr_edge(e)[n], count++);

         reverse(F, e2fbegin[e].first,  count,wrap); // l initial
         reverse(F, e2fsides[e].first,  count); // l

         // base
         metamesh_form2form(e,edge, edge2face, oface,F);
      }
}

}  // internal
}  // metamesh

#endif
