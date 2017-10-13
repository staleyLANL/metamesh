/* -*- C++ -*- */

#ifndef METAMESH_EXTRUDE01
#define METAMESH_EXTRUDE01

/*

This file provides functionality for 0-form to 1-form extrusions.

Variants:

mesh<node> to mesh<node,edge<node>>
   layer:   node to node
   filling: node to edge<node>

*/

// Whole file
namespace metamesh {
namespace internal {



// =============================================================================
// extrude_info: 0-to-1
// =============================================================================

// 1 = output form
template<class IMESH, class OMESH>
class extrude_info<IMESH,OMESH,1> {

   using onode = typename OMESH::node_t;

public:

   // ------------------------
   // data
   // ------------------------

   // number of nodes in input mesh; looper
   const std::size_t nnode;  const loop n;

   // node index+1's in output mesh; 0 = uninitialized
   std::vector<std::size_t>
      ncurr,  // for current  layer
      nprev,  // for previous layer
      ninit;  // for initial  layer

   // proposed new layer
   std::vector<onode> proposed;  // nodes themselves
   std::vector< bool> nodeison;  // nodes on/true?


   // ------------------------
   // constructor
   // ------------------------

   explicit extrude_info(
      const std::size_t _nnode
   ) :
      nnode(_nnode), n(nnode),

      ncurr(nnode,0),
      nprev(nnode,0),
      ninit(nnode,0),

      proposed(nnode),
      nodeison(nnode)
   { }
};



// =============================================================================
// Macros
// =============================================================================

// extrude_logic_01_template
#define extrude_logic_01_template\
   template<\
      class inode, class iedge, class iface, class icell, class ibase,\
      class onode, class oedge, class oface, class ocell, class obase,\
      class PATH,\
      class NODE_ON, class N2N, class N2E\
   >

// extrude_logic_01_type
#define extrude_logic_01_type\
   extrude_logic_01<\
      inode, iedge, iface, icell, ibase,\
      onode, oedge, oface, ocell, obase,\
      PATH,\
      NODE_ON, N2N, N2E\
   >

// extrude_logic_01_function
#define extrude_logic_01_function(fun)\
   extrude_logic_01_template\
   void extrude_logic_01_type::fun(\
      const std::size_t iteration,\
      const bool tie, const bool trim, const bool wrap\
   )



// =============================================================================
// extrude_logic_01
// Function object; an instance is sent to the general extrude_logic()
// =============================================================================

extrude_logic_01_template
class extrude_logic_01 :
   public internal::extrude_info<
      metamesh::mesh<inode,iedge,iface,icell,ibase,0>,
      metamesh::mesh<onode,oedge,oface,ocell,obase,1>,
      1
   >
{
public:

   using extrude_info = internal::extrude_info<
      metamesh::mesh<inode,iedge,iface,icell,ibase,0>,
      metamesh::mesh<onode,oedge,oface,ocell,obase,1>, 1
   >;

   using extrude_info::nnode;
   using extrude_info::n;
   using extrude_info::ncurr;
   using extrude_info::nprev;
   using extrude_info::ninit;
   using extrude_info::proposed;
   using extrude_info::nodeison;

private:

   // types
   using value_t = typename onode::value_t;  // output node value_t

   // meshes
   const mesh<inode,iedge,iface,icell,ibase,0> &in;
   /* */ mesh<onode,oedge,oface,ocell,obase,1> &out;

   // functors
   const PATH &path;
   const NODE_ON &node_on;  const N2N &node2node;  const N2E &node2edge;

   // qqq The following issue should eventually be handled with another functor
   // eps, length scaling
   const value_t eps;  value_t scaling;

   // for convenience
   // qqq no curr_node?
   inline const onode &init_node(const std::size_t n) const
      { return out.node[ninit[n]-1]; }
   inline const onode &prev_node(const std::size_t n) const
      { return out.node[nprev[n]-1]; }

public:

   // constructor
   explicit extrude_logic_01(
      const mesh<inode,iedge,iface,icell,ibase,0> &,
      /* */ mesh<onode,oedge,oface,ocell,obase,1> &,
      const PATH &,
      const NODE_ON &, const N2N &, const N2E &
   );

   // callbacks
   // Parameters: (iteration,tie,trim,wrap)
   void layer_propose     (const std::size_t, const bool,const bool,const bool);
   void layer_submit      (const std::size_t, const bool,const bool,const bool);

   void trim_vs_previous  (const std::size_t, const bool,const bool,const bool);
   void trim_vs_initial   (const std::size_t, const bool,const bool,const bool);

   void filling_make      (const std::size_t, const bool,const bool,const bool);

   void previous_eq_curr  (const std::size_t, const bool,const bool,const bool);
   void current_eq_initial(const std::size_t, const bool,const bool,const bool);
};



// =============================================================================
// Constructor
// =============================================================================

extrude_logic_01_template
extrude_logic_01_type::extrude_logic_01(
   const mesh<inode,iedge,iface,icell,ibase,0> &i,
   /* */ mesh<onode,oedge,oface,ocell,obase,1> &o,
   const PATH &p,
   const NODE_ON &non, const N2N &n2n, const N2E &n2e
) :
   extrude_info(
      i.node.size()
   ),
   in(i), out(o), path(p),
   node_on(non), node2node(n2n), node2edge(n2e),
   eps(get_eps<value_t>())
{
   // scaling is computed later
}



// =============================================================================
// layer_propose
// layer_submit
// =============================================================================

// layer_propose
extrude_logic_01_function(layer_propose)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   // Nodes
   while (n()) {
      // Propagate the base, then propagate the coordinate. This ordering
      // is good if the user chooses to do both in the latter function,
      // in which case the intended base propagation won't be overwritten.

      if ((void *)&node2node != (void *)&metamesh::noop)
      node2node.
      node2node(in,out,iteration,std::size_t(n),in.node[n],proposed[n]);
      path.
      path     (in,out,iteration,std::size_t(n),in.node[n],proposed[n]);

      nodeison[n] =
      node_on.
      node_on  (in,out,iteration,std::size_t(n),in.node[n],proposed);
   }

   // Determine length scaling
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
extrude_logic_01_function(layer_submit)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   // Nodes
   while (n())
      if (nodeison[n]) {
         out.push(proposed[n]);
         book(out.node, ncurr, ninit, n);
      }
}



// =============================================================================
// trim_vs_previous
// trim_vs_initial
// =============================================================================

// trim_vs_previous
extrude_logic_01_function(trim_vs_previous)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   while (n())
      if (nodeison[n] && nprev[n] &&
          near(proposed[n], prev_node(n), scaling,eps)) {
         nodeison[n] = false;  // duplicate of previous; turn back off

         // Compare trim_vs_initial() below. Here the update is unnecessary,
         // because ncurr[n] wouldn't have been updated yet anyway.
         assert(ncurr[n] == nprev[n]);  // remove sometime
      }
}



// trim_vs_initial
extrude_logic_01_function(trim_vs_initial)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   while (n())
      if (nodeison[n] && ninit[n] &&
          near(proposed[n], init_node(n), scaling,eps)) {
         nodeison[n] = false;  // duplicate of initial; turn back off

         // We turned off the node only because it was near to the initial
         // node, so the rightful current node IS this initial node.
         ncurr[n] = ninit[n];
      }
}



// =============================================================================
// filling_make
// =============================================================================

// filling_make
extrude_logic_01_function(filling_make)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;

   // Note: changed(nprev,ncurr,n) is NOT equivalent to nodeison[n] && nprev[n].
   //
   // In fact:
   //    nodeison[n] && nprev[n]  ===>
   //    changed(nprev,ncurr,n)
   // but
   //    changed(nprev,ncurr,n)   ===>
   //       EITHER  nodeison[n] && nprev[n]
   //       OR     !nodeison[n] && ncurr[n]==ninit[n] && nprev[n] != ninit[n])
   //
   // We thus use changed() to capture the correct behavior at both "beginning"
   // and "end" of extrusion. We create filling iff we have two distinct layers.

   // Nodes to edges
   while (n())
      if (changed(nprev, ncurr, n)) {
         oedge E;  E.clear(2);
         E.push(nprev[n]-1, 0);
         E.push(ncurr[n]-1, 1);
         metamesh_form2form(n,node, node2edge, oedge,E);
      }
}



// =============================================================================
// previous_eq_curr
// current_eq_initial
// =============================================================================

// previous_eq_curr
extrude_logic_01_function(previous_eq_curr)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;
   nprev = ncurr;
}

// current_eq_initial
extrude_logic_01_function(current_eq_initial)
{
   (void)iteration; (void)tie; (void)trim; (void)wrap;
   ncurr = ninit;
}



// =============================================================================
// extrude01
//    in, path, more, node_on, out, tying, trimming,
//    action,
//    node2node, node2edge
// =============================================================================

// qqq Note: I think it may be true that the stuff involving the PATH call is
// the same for 0-1, 1-2, and 2-3 extrusions. If we can verify this, then try
// try to handle PATH exclusively in the general extrude_logic() function, and
// then chuck its use in our extrude_logic_* function objects and functions.

template<
   class inode, class iedge, class iface, class icell, class ibase,
   class onode, class oedge, class oface, class ocell, class obase,
   class PATH, class MORE, class ACTION,
   class NODE_ON, class N2N, class N2E
>
mesh<onode,oedge,oface,ocell,obase,1> &extrude01(
   // extrude_info pointer
   const extrude_info<
      metamesh::mesh<inode,iedge,iface,icell,ibase,0>,
      metamesh::mesh<onode,oedge,oface,ocell,obase,1>,
      1
   > * &ptr,

   // input mesh
   const mesh<inode,iedge,iface,icell,ibase,0> &in,

   // extrusion path, continuation condition
   const PATH &path,
   const MORE &more,

   // masking
   const NODE_ON &node_on,

   // output mesh
   mesh<onode,oedge,oface,ocell,obase,1> &out,

   // tie and trim flags
   const tie_t  tying,
   const trim_t trimming,

   // miscellaneous functors
   const ACTION &action,
   const N2N &node2node, const N2E &node2edge
) {
   // Prefix: clear output mesh, check input mesh
   if (!extrude_prefix(in,out))
      return out;

   // Extrude-logic callback object
   extrude_logic_01_type plugins(
      in, out, path,
      node_on, node2node, node2edge
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

// Macros: undefine; no longer need
#undef extrude_logic_01_template
#undef extrude_logic_01_type
#undef extrude_logic_01_function

#endif
