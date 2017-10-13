/* -*- C++ -*- */

#ifndef METAMESH_SUPPORT
#define METAMESH_SUPPORT

// This file provides miscellaneous support constructs for the extrude
// capabilities.



// =============================================================================
// tie
// trim
// =============================================================================

namespace metamesh {

// tie_t
// Extrusion flag: should the extruded mesh tie back to itself at the end?
enum tie_t {
   tie,
   notie, no_tie = notie
};

// trim_t
// Extrusion flag: should successive "duplicate" points be folded into one?
enum trim_t {
   trim,
   notrim, no_trim = notrim
};

}  // metamesh



// =============================================================================
// Miscellaneous
// =============================================================================

// Macro: metamesh_form2form
// This will be #undefined in a different file
#define metamesh_form2form(f,from, call, to_t,T)\
   to_t &back = out.push(T);\
   if ((void *)&call != (void *)&metamesh::noop)\
      call.call(in,out, iteration,std::size_t(f), in.from[f],back)



// extrude_info
namespace metamesh {
namespace internal {

template<
   class  IMESH,
   class  OMESH,
   std::size_t oform = OMESH::form
>
class extrude_info {
};

}  // internal
}  // metamesh



// =============================================================================
// near
// distance
// =============================================================================

// qqq
// 1. The concept here should eventually go elsewhere, and be user-definable.
// 2. Eventually, we may want to bypass the always-3d "point" class here.
// Perhaps that class should be only for interfacing with the kip library.
// And, we don't square() or sqrt(square()), which is what we'll get,
// respectively, in the two functions below, in the 1d node case. Think,
// eventually about reworking the present concept differently, and having
// point be strictly for kip.

namespace metamesh {
namespace internal {

// near
// Are two nodes "near" each other, given a length scale and a tolerance?
// qqq Consider swapping len,eps order, and defaulting len = 1.
template<class terms, class base, std::size_t dimension>
inline bool near(
   const node<terms,base,dimension> &a,
   const node<terms,base,dimension> &b,
   const typename node<terms,base,dimension>::value_t &len,  // length scale
   const typename node<terms,base,dimension>::value_t &eps   // tolerance
) {
   // <=, not <, so that identical nodes still test as near when eps == 0
   using value_t = typename node<terms,base,dimension>::value_t;
   return mod2(point<value_t>(a) - point<value_t>(b)) <= op::square(len*eps);
}



// distance
// Distance between two nodes.
template<class terms, class base, std::size_t dimension>
inline typename node<terms,base,dimension>::value_t distance(
   const node<terms,base,dimension> &a,
   const node<terms,base,dimension> &b
) {
   using value_t = typename node<terms,base,dimension>::value_t;
   return mod(point<value_t>(a) - point<value_t>(b));
}

}  // internal
}  // metamesh



// =============================================================================
// extrude_prefix
// extrude_suffix
// Template parameter notation: i for input mesh, o for output mesh
// =============================================================================

namespace metamesh {
namespace internal {

// extrude_prefix
// bool (in,out)
// Clear, and return true or false (did the input mesh .check()?)
template<
   class inode, class iedge, class iface, class icell,
   class ibase, std::size_t iform,
   class onode, class oedge, class oface, class ocell,
   class obase
>
inline bool extrude_prefix(
   const mesh<inode,iedge,iface,icell,ibase,iform  > &in,
         mesh<onode,oedge,oface,ocell,obase,iform+1> &out
) {
   // clear output (it'll receive extrusion)
   out.clear();

   // check input (to which extrusion will be applied)
   return
      in.check("Detected in input mesh.check() before extrude()") !=
      diagnostic_error;  // fine, as long as there's no error
}



// extrude_suffix
// out (out)
// Check output (no specific additional action if problem); return output
template<
   class onode, class oedge, class oface, class ocell,
   class obase, std::size_t oform
>
inline
   mesh<onode,oedge,oface,ocell,obase,oform> &extrude_suffix(
   mesh<onode,oedge,oface,ocell,obase,oform> &out
) {
   // check output
   (void)out.check("Detected in output mesh.check() after extrude()");
   return out;
}

}  // internal
}  // metamesh



// =============================================================================
// is_node_else
// is_edge_else
// is_face_else
// is_cell_else
// =============================================================================

namespace metamesh {
namespace internal {

// General: NOT node, edge, face, cell; choose "else"/no
template<class T, class yes, class no> struct is_node_else { using type = no; };
template<class T, class yes, class no> struct is_edge_else { using type = no; };
template<class T, class yes, class no> struct is_face_else { using type = no; };
template<class T, class yes, class no> struct is_cell_else { using type = no; };



// Specific: node, edge, face, cell; choose "if"/yes
template<class terms, class base, std::size_t dimension, class yes, class no>
struct is_node_else<node<terms,base,dimension>,yes,no> { using type = yes; };

template<class terms, class base, std::size_t dimension, class yes, class no>
struct is_edge_else<edge<terms,base,dimension>,yes,no> { using type = yes; };

template<class terms, class base, std::size_t dimension, class yes, class no>
struct is_face_else<face<terms,base,dimension>,yes,no> { using type = yes; };

template<class terms, class base, std::size_t dimension, class yes, class no>
struct is_cell_else<cell<terms,base,dimension>,yes,no> { using type = yes; };

}  // internal
}  // metamesh



// =============================================================================
// book
// changed
// qqq Review usage, then put reasonable description here.
// =============================================================================

namespace metamesh {
namespace internal {

// book
template<class CONTAINER>
inline void book(
   const CONTAINER &container,  // qqq just vector<>, or general?
   std::vector<std::size_t> &curr,
   std::vector<std::size_t> &init,
   const std::size_t i
) {
   // update current (and initial, if necessary)
   curr[i] = container.size();
   if (!init[i])
      init[i] = container.size();
}



// changed
inline bool changed(
   const std::vector<std::size_t> &prev,
   const std::vector<std::size_t> &curr,
   const std::size_t i
) {
   // is previous defined, and current different?
   return prev[i] && curr[i] != prev[i];
}

}  // internal
}  // metamesh



// =============================================================================
// forward
// reverse
// qqq Review usage, then put reasonable description here.
// =============================================================================

namespace metamesh {
namespace internal {

// forward
template<class TO, class CONTAINER>
inline void forward(
   TO &to, CONTAINER &container,
   std::size_t &count,  // reference!
   const bool doit = true
) {
   if (doit) {
      const loop i(container);
      while (i.more())
         to.push(container[i]-1, count++);  // (value,index)
      container.clear();  // clear after use
   }
}

// qqq Maybe asserts above and below, that container[i] >= 1 ???

// reverse
template<class TO, class CONTAINER>
inline void reverse(
   TO &to, CONTAINER &container,
   std::size_t &count,  // reference!
   const bool doit = true
) {
   if (doit) {
      const loop i(container);
      while (i.less())
         to.push(container[i]-1, count++);  // (value,index)
      container.clear();  // clear after use
   }
}

}  // internal
}  // metamesh



// =============================================================================
// extrude_logic
// =============================================================================

/*
qqq
Document the meaning of each of these:
   ( ) layer_propose
   ( ) layer_submit
   ( ) previous_eq_curr
   ( ) trim_vs_previous
   ( ) filling_make
   ( ) trim_vs_initial
   ( ) current_eq_initial
Each is called with (iteration, tie, trim, wrap)

--------------------------------------------------------------------------------
   notie, notrim      notie, trim        tie, notrim        tie, trim
-------------------------------------------------------------------------------

   layer_propose      layer_propose      layer_propose      layer_propose
   layer_submit       layer_submit       layer_submit       layer_submit
   previous_eq_curr   previous_eq_curr   previous_eq_curr   previous_eq_curr
------                                                                   ------
   layer_propose      layer_propose      layer_propose      layer_propose
                      trim_vs_previous                      trim_vs_previous
   layer_submit       layer_submit       layer_submit       layer_submit
   filling_make       filling_make       filling_make       filling_make
   previous_eq_curr   previous_eq_curr   previous_eq_curr   previous_eq_curr
------                                                                   ------
   ...                ...                ...                ...
------                                                                   ------
   layer_propose      layer_propose      layer_propose      layer_propose
                      trim_vs_previous                      trim_vs_previous
   layer_submit       layer_submit       layer_submit       layer_submit
   filling_make       filling_make       filling_make       filling_make
   previous_eq_curr   previous_eq_curr   previous_eq_curr   previous_eq_curr
------                                                                   ------
   layer_propose      layer_propose      layer_propose      layer_propose
                      trim_vs_previous                      trim_vs_previous
                                                            trim_vs_initial
   layer_submit       layer_submit       layer_submit       layer_submit
   filling_make       filling_make       filling_make       filling_make
   previous_eq_curr   previous_eq_curr   previous_eq_curr   previous_eq_curr
------                                                                   ------
   layer_propose      layer_propose      current_eq_initial current_eq_initial
                      trim_vs_previous
   layer_submit       layer_submit
   filling_make       filling_make       filling_make       filling_make

--------------------------------------------------------------------------------
   notie, notrim      notie, trim        tie, notrim        tie, trim
--------------------------------------------------------------------------------
*/

namespace metamesh {
namespace internal {

template<
   class inode, class iedge, class iface, class icell, class ibase,
   std::size_t iform,
   class onode, class oedge, class oface, class ocell, class obase,
   class MORE, class ACTION,
   class PLUGINS
>
inline void extrude_logic(
   // input and output meshes
   const mesh<inode,iedge,iface,icell,ibase,iform  > &in,
   /* */ mesh<onode,oedge,oface,ocell,obase,iform+1> &out,

   // continue condition, action, and form-specific code to be called
   // within the extrude-logic infrastructure

   // User-supplied behaviors
   MORE   &more,    // extrusion-continuation condition
   ACTION &action,  // general end-of-step action to perform

   // Amalgamation containing extrusion-logic callbacks that depend on the
   // form (e.g., 1-form to 2-form extrusion); and additional user-supplied
   // behaviors that, unlike "more" and "action" (see above) aren't handled
   // directly in this bird's-eye, general-extrusion-logic function. Placing
   // all this together into one parameter perhaps wasn't the best choice in
   // terms of understandability, and we might consider splitting the two
   // types of contents into two variables. On the other hand, the form-
   // dependent callbacks themselves make use of the user-defined behaviors,
   // so, perhaps, it's helpful to put them all together.
   PLUGINS &plugins,

   // tie and trim flags
   const tie_t  tying,
   const trim_t trimming
) {
   /*
   The plugins variable (see above) has these logic-specializing functions:
      layer_propose
      layer_submit
      previous_eq_curr
      trim_vs_previous
      filling_make
      trim_vs_initial
      current_eq_initial
   Each is called with (iteration, tie, trim, wrap).
   */

   // flags
   const bool tie  = tying    == metamesh::tie;   // tie back to initial?
   const bool trim = trimming == metamesh::trim;  // trim successive duplicates?

   // iteration#
   std::size_t iteration = 0;

   // qqq
   // As far as I can tell, in my 2017 review...
   //    current = put in another layer
   //    next    = put in another layer beyond that
   //    further = and yet another
   // Note that we'll ALWAYS get >= 1 layer when we extrude. Thus the number
   // of times more() returns true will be the number of fillings, with the
   // number of layers one more than that. That arguably wouldn't be a good
   // system for a general looping construct, but I think it makes sense for
   // our mesh-extrusion concept.
   // It might be worthwhile sometime to write out the following as pseudocode
   // for each trim/tie true/false scenario.

   bool current = true,
        further,  next = more.more(in,out, iteration);

   do {
      further = next && (more.more(in,out, iteration+1));

      // qqq Can current NOT be true in the following context???
      assert(current == true);
      const bool wrap = iteration && tie && current && !next;

      if (wrap) {
         // for the current layer, use the initial layer
         plugins.current_eq_initial   (iteration,tie,trim,wrap);
      } else {
         // create the current layer
         plugins.layer_propose        (iteration,tie,trim,wrap);
         if (trim && iteration) {
            // we're trimming, and there's a previous layer to trim against
            plugins.trim_vs_previous  (iteration,tie,trim,wrap);
            if (!further && tie)
               plugins.trim_vs_initial(iteration,tie,trim,wrap);
         }
         plugins.layer_submit         (iteration,tie,trim,wrap);
      }

      if (iteration)
         plugins.filling_make         (iteration,tie,trim,wrap);

      if (next)
         plugins.previous_eq_curr     (iteration,tie,trim,wrap);

      /**/
      current = next;
      next = further;
   } while (action.action(in,out, iteration++), current);

      /**/

      /*
   } while (action.action(in,out, iteration++),
            current = next, next = further, current);
      */

}

}  // internal
}  // metamesh

#endif
