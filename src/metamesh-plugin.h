/* -*- C++ -*- */

#ifndef METAMESH_PLUGIN
#define METAMESH_PLUGIN

// This file provides plugin-related support constructs for the metamesh
// library's extrude capabilities.



// =============================================================================
// epsilon
// qqq This concept isn't actually a plugin at the moment. Eventually rework
// so that it is; then, the below stuff will change in some reasonable way.
// =============================================================================

namespace metamesh {
namespace internal {

// epsilon_function
inline quad &epsilon_function(void)
{
   static quad epsilon = 0.0L;
   return epsilon;
}

// get_eps
template<class real>
inline real get_eps(void)
{
   // For 0, this function computes something from std::numeric_limits;
   // for nonzero, it just returns the nonzero value.
   return std::abs(
      epsilon_function() != 0.0L
    ? real(epsilon_function())
    : std::pow(real(10), -2*std::numeric_limits<real>::digits10/real(3))
   );
}

}  // internal
}  // metamesh



// epsilon
namespace metamesh {
namespace {
   quad &epsilon = internal::epsilon_function();
}
}  // metamesh



// =============================================================================
// assign
// Base propagation:
//    node2node
//    node2edge
//    edge2edge
//    edge2face
//    face2face
//    face2cell
// Sets output mesh.base() = input mesh.base(). Assumes the assignment works.
// =============================================================================

namespace metamesh {
namespace internal {

// assign_class
class assign_class {
public:

   // constructor
   inline explicit assign_class(void)
   { }

   // base propagation
   template<class IMESH, class OMESH>
   metamesh_macro_node2node(IMESH,OMESH)
      { metamesh_macro_node2node_param;  omesh.base() = imesh.base(); }
   template<class IMESH, class OMESH>
   metamesh_macro_node2edge(IMESH,OMESH)
      { metamesh_macro_node2edge_param;  omesh.base() = imesh.base(); }
   template<class IMESH, class OMESH>
   metamesh_macro_edge2edge(IMESH,OMESH)
      { metamesh_macro_edge2edge_param;  omesh.base() = imesh.base(); }
   template<class IMESH, class OMESH>
   metamesh_macro_edge2face(IMESH,OMESH)
      { metamesh_macro_edge2face_param;  omesh.base() = imesh.base(); }
   template<class IMESH, class OMESH>
   metamesh_macro_face2face(IMESH,OMESH)
      { metamesh_macro_face2face_param;  omesh.base() = imesh.base(); }
   template<class IMESH, class OMESH>
   metamesh_macro_face2cell(IMESH,OMESH)
      { metamesh_macro_face2cell_param;  omesh.base() = imesh.base(); }
};



// assign_function
inline const assign_class &assign_function(void)
{
   static const assign_class assign;
   return assign;
}

}  // internal
}  // metamesh



// assign
namespace metamesh {
namespace {
   const internal::assign_class &assign = internal::assign_function();
}
}  // metamesh



// =============================================================================
// noop
// Base propagation:
//    node2node
//    node2edge
//    edge2edge
//    edge2face
//    face2face
//    face2cell
// General end-of-step action:
//    action
// No-op (no operation, i.e. do-nothing function) in each case.
// =============================================================================

namespace metamesh {
namespace internal {

// noop_class
class noop_class {
public:

   // constructor
   inline explicit noop_class(void)
   { }

   // base propagation
   template<class IMESH, class OMESH>
   metamesh_macro_node2node(IMESH,OMESH) { metamesh_macro_node2node_param; }
   template<class IMESH, class OMESH>
   metamesh_macro_node2edge(IMESH,OMESH) { metamesh_macro_node2edge_param; }
   template<class IMESH, class OMESH>
   metamesh_macro_edge2edge(IMESH,OMESH) { metamesh_macro_edge2edge_param; }
   template<class IMESH, class OMESH>
   metamesh_macro_edge2face(IMESH,OMESH) { metamesh_macro_edge2face_param; }
   template<class IMESH, class OMESH>
   metamesh_macro_face2face(IMESH,OMESH) { metamesh_macro_face2face_param; }
   template<class IMESH, class OMESH>
   metamesh_macro_face2cell(IMESH,OMESH) { metamesh_macro_face2cell_param; }

   // action
   template<class IMESH, class OMESH>
   metamesh_macro_action(IMESH,OMESH)
      { metamesh_macro_action_param; }
};



// noop_function
inline const noop_class &noop_function(void)
{
   static const noop_class noop;
   return noop;
}

}  // internal
}  // metamesh



// noop
namespace metamesh {
namespace {
   const internal::noop_class &noop = internal::noop_function();
}
}  // metamesh



// =============================================================================
// on
// off
// Layer-element masking:
//    node_on
//    edge_on
//    face_on
// Returns true for on, false for off.
// =============================================================================

namespace metamesh {
namespace internal {

// mask_class
class mask_class {
   bool value;

public:

   // constructor
   inline explicit mask_class(const bool b) :
      value(b)
   { }

   // masking
   template<class IMESH, class OMESH>
   metamesh_macro_node_on(IMESH,OMESH)
      { metamesh_macro_node_on_param;  return value; }
   template<class IMESH, class OMESH>
   metamesh_macro_edge_on(IMESH,OMESH)
      { metamesh_macro_edge_on_param;  return value; }
   template<class IMESH, class OMESH>
   metamesh_macro_face_on(IMESH,OMESH)
      { metamesh_macro_face_on_param;  return value; }
};



// on_function
inline const mask_class &on_function(void)
{
   static const mask_class on(true);
   return on;
}

// off_function
inline const mask_class &off_function(void)
{
   static const mask_class off(false);
   return off;
}

}  // internal
}  // metamesh



// on, off
namespace metamesh {
namespace {
   const internal::mask_class &on  = internal:: on_function();
   const internal::mask_class &off = internal::off_function();
}
}  // metamesh



// =============================================================================
// random
// Layer-element masking:
//    node_on
//    edge_on
//    face_on
// Returns true if drand48() < the given probability, false otherwise.
// Note: Users should make their own instances of this class; we'll therefore
// put it in namespace metamesh, not metamesh::internal as with others above.
// =============================================================================

namespace metamesh {

// random
class random {
   double probability;

public:

   // constructor
   inline explicit random(const double &p) :
      probability(p)
   {
      // qqq Consider print Note if probability is outside of meaningful range
   }

   // masking
   template<class IMESH, class OMESH>
   metamesh_macro_node_on(IMESH,OMESH)
      { metamesh_macro_node_on_param;  return drand48() < probability; }
   template<class IMESH, class OMESH>
   metamesh_macro_edge_on(IMESH,OMESH)
      { metamesh_macro_edge_on_param;  return drand48() < probability; }
   template<class IMESH, class OMESH>
   metamesh_macro_face_on(IMESH,OMESH)
      { metamesh_macro_face_on_param;  return drand48() < probability; }
};

}  // metamesh



// =============================================================================
// extrude_plugin
// =============================================================================

namespace metamesh {

   /*
qqq
write this
have 01, 12, 23 variants
set of all plugins except path and more.
something users could derive their own class from.
then make extrude() variants in extrude.hh to accept single functor.
   */

}  // metamesh

#endif
