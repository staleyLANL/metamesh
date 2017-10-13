/* -*- C++ -*- */

#ifndef METAMESH_FEDGE
#define METAMESH_FEDGE

// For the
//    face<edge>
// extrude 1-2 variant, this file provides layer_submit() and filling_make().

// Whole file
namespace metamesh {
namespace internal {



// =============================================================================
// layer_submit
// =============================================================================

extrude_logic_12_template
void extrude_logic_12_type::layer_submit(
   const typename is_edge_else<face_terms,std::size_t,stub>::type iteration,
   const bool tie, const bool trim, const bool wrap
) {
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   // Equivalent to layer_submit for face<node>, except without
   // the now-unnecessary side-node bookkeeping.

   // Nodes
   while (n())
      if (nodeison[n]) {
         out.push(proposed[n]);
         book(out.node, ncurr, ninit, n);
      }

   // Edges
   while (e())
      if (edgeison[e])
         submit_edge_if_appropriate(in.edge[e].size(), iteration, trim);
}



// =============================================================================
// filling_make
// =============================================================================

extrude_logic_12_template
void extrude_logic_12_type::filling_make(
   const typename is_edge_else<face_terms,std::size_t,stub>::type iteration,
   const bool tie, const bool trim, const bool wrap
) {
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   // Equivalent to filling_make for face<node>, except with
   // the now-necessary side-edge bookkeeping.

   // Nodes to edges
   while (n())
      if (changed(nprev, ncurr, n)) {
         oedge E;  E.clear(2);
         E.push(nprev[n]-1, 0);
         E.push(ncurr[n]-1, 1);

         metamesh_form2form(n,node, node2edge, oedge,E);
         n2e[n] = out.edge.size();  // see remark below
      }

   // Edges to faces
   while (e()) {
      const std::size_t nnode = in.edge[e].size();
      const loop n(nnode);
      idx_vec_pair &fsides = eprev[e] ? e2fsides[e] : e2fbegin[e];

      // Record sides. This is why we need n2e. We start with the layer
      // edge, find its endpoints, use n2e to find the endpoints' filling
      // edges, and record these filling edges as face sides.
      const std::size_t a = nnode ? in.edge[e][n.min()] : 0;
      const std::size_t b = nnode ? in.edge[e][n.max()] : 0;

      if (nnode && changed(nprev, ncurr, a)) fsides.first .push_back(n2e[a]);
      if (nnode && changed(nprev, ncurr, b)) fsides.second.push_back(n2e[b]);

      // Edges to faces
      if (changed(eprev, ecurr, e)) {
         std::size_t count = 0;  oface F;  F.clear(
               2    + e2fsides[e].second.size()  // left edge(s)
            + (wrap ? e2fbegin[e].second.size() : 0)
            + (wrap ? e2fbegin[e].first .size() : 0)
            +         e2fsides[e].first .size()  // right edge(s)
         );

         F.push(eprev[e]-1, count++);  // bottom
         forward(F, e2fsides[e].second, count); // r
         forward(F, e2fbegin[e].second, count,wrap); // r initial
         F.push(ecurr[e]-1, count++);  // top
         reverse(F, e2fbegin[e].first,  count,wrap); // l initial
         reverse(F, e2fsides[e].first,  count); // l

         // base
         metamesh_form2form(e,edge, edge2face, oface,F);
      }
   }
}

}  // internal
}  // metamesh

// Macros: undefine; no longer need
#undef extrude_logic_12_template
#undef extrude_logic_12_type
#undef extrude_logic_12_function

#endif
