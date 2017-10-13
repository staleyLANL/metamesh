/* -*- C++ -*- */

#ifndef METAMESH_COORD
#define METAMESH_COORD

// This file provides some coordinate systems:
//
//      0d cartesian     ()
//      1d cartesian     (x)
//      2d cartesian     (x,y)
//      3d cartesian     (x,y,z)
//      2d polar         (r,t)
//      2d cylindrical   (r,z)
//      3d cylindrical   (r,t,z)
//      3d spherical     (r,t,p)
//
//   Note: these provide the following unions:
//
//      r, radius, s
//      t, theta
//      p, phi



// =============================================================================
// Coordinate systems
// See specializations below
// =============================================================================

namespace metamesh {

// component
// helper class
template<std::size_t n>
class component {
};


// cartesian, polar, cylindrical, spherical
#ifdef METAMESH_NO_DEFAULT
   template<std::size_t dimension, class real> class cartesian   { };
   template<std::size_t dimension, class real> class polar       { };
   template<std::size_t dimension, class real> class cylindrical { };
   template<std::size_t dimension, class real> class spherical   { };
#else
   template<std::size_t dimension,     class real = default_real_t>
   class cartesian   { };
   template<std::size_t dimension = 2, class real = default_real_t>
   class polar       { };
   template<std::size_t dimension = 3, class real = default_real_t>
   class cylindrical { };
   template<std::size_t dimension = 3, class real = default_real_t>
   class spherical   { };
#endif

}  // metamesh



// =============================================================================
// 0d cartesian
// =============================================================================

namespace metamesh {

template<class real>
class cartesian<0,real> {
public:

   // dimension, value_t
   static const std::size_t dimension = 0;
   using value_t = real;

   // coordinates
   // none!

   // default
   inline explicit cartesian(void) { }

   // conversion to point<real>
   inline operator point<real>(void) const
   {
      return point<real>(0,0,0);
   }
};

}  // metamesh



// =============================================================================
// 1d cartesian
// =============================================================================

namespace metamesh {

template<class real>
class cartesian<1,real> {
public:

   // dimension, value_t
   static const std::size_t dimension = 1;
   using value_t = real;

   // coordinates
   real x;

   // default
   inline explicit cartesian(void) { }

   // cartesian(x)
   inline explicit cartesian(const real &_x) :
      x(_x)
   { }

   // value
   inline real &value(const component<0>) { return x; }

   // value - const
   inline const real &value(const component<0>) const { return x; }

   // label
   static inline const char *label(const component<0>) { return "x"; }

   // conversion to point<real>
   inline operator point<real>(void) const
   {
      return point<real>(x,0,0);
   }
};

}  // metamesh



// =============================================================================
// 2d cartesian
// =============================================================================

namespace metamesh {

template<class real>
class cartesian<2,real> {
public:

   // dimension, value_t
   static const std::size_t dimension = 2;
   using value_t = real;

   // coordinates
   real x;
   real y;

   // default
   inline explicit cartesian(void) { }

   // cartesian(x,y)
   inline explicit cartesian(const real &_x, const real &_y) :
      x(_x), y(_y)
   { }

   // value
   inline real &value(const component<0>) { return x; }
   inline real &value(const component<1>) { return y; }

   // value - const
   inline const real &value(const component<0>) const { return x; }
   inline const real &value(const component<1>) const { return y; }

   // label
   static inline const char *label(const component<0>) { return "x"; }
   static inline const char *label(const component<1>) { return "y"; }

   // conversion to point<real>
   inline operator point<real>(void) const
   {
      return point<real>(x,y,0);
   }
};

}  // metamesh



// =============================================================================
// 3d cartesian
// =============================================================================

namespace metamesh {

template<class real>
class cartesian<3,real> {
public:

   // dimension, value_t
   static const std::size_t dimension = 3;
   using value_t = real;

   // coordinates
   real x;
   real y;
   real z;

   // default
   inline explicit cartesian(void) { }

   // cartesian(x,y,z)
   inline explicit cartesian(const real &_x, const real &_y, const real &_z) :
      x(_x), y(_y), z(_z)
   { }

   // value
   inline real &value(const component<0>) { return x; }
   inline real &value(const component<1>) { return y; }
   inline real &value(const component<2>) { return z; }

   // value - const
   inline const real &value(const component<0>) const { return x; }
   inline const real &value(const component<1>) const { return y; }
   inline const real &value(const component<2>) const { return z; }

   // label
   static inline const char *label(const component<0>) { return "x"; }
   static inline const char *label(const component<1>) { return "y"; }
   static inline const char *label(const component<2>) { return "z"; }

   // conversion to point<real>
   inline operator point<real>(void) const
   {
      return point<real>(x,y,z);
   }
};

}  // metamesh



// =============================================================================
// 2d polar
// =============================================================================

namespace metamesh {

template<class real>
class polar<2,real> {
public:

   // dimension, value_t
   static const std::size_t dimension = 2;
   using value_t = real;

   // coordinates
   union { real r, radius, s; };
   union { real t, theta; };

   // default
   inline explicit polar(void) { }

   // polar(r,t)
   inline explicit polar(const real &_r, const real &_t) :
      r(_r), t(_t)
   { }

   // value
   inline real &value(const component<0>) { return r; }
   inline real &value(const component<1>) { return t; }

   // value - const
   inline const real &value(const component<0>) const { return r; }
   inline const real &value(const component<1>) const { return t; }

   // label
   static inline const char *label(const component<0>) { return "r"; }
   static inline const char *label(const component<1>) { return "t"; }

   // conversion to point<real>
   inline operator point<real>(void) const
   {
      return point<real>(
         r*std::cos(t),
         r*std::sin(t),
         0
      );
   }
};

}  // metamesh



// =============================================================================
// 2d cylindrical
// =============================================================================

namespace metamesh {

template<class real>
class cylindrical<2,real> {
public:

   // dimension, value_t
   static const std::size_t dimension = 2;
   using value_t = real;

   // coordinates
   union { real r, radius, s; };
   real z;

   // default
   inline explicit cylindrical(void) { }

   // cylindrical(r,z)
   inline explicit cylindrical(const real &_r, const real &_z) :
      r(_r), z(_z)
   { }

   // value
   inline real &value(const component<0>) { return r; }
   inline real &value(const component<1>) { return z; }

   // value - const
   inline const real &value(const component<0>) const { return r; }
   inline const real &value(const component<1>) const { return z; }

   // label
   static inline const char *label(const component<0>) { return "r"; }
   static inline const char *label(const component<1>) { return "z"; }

   // conversion to point<real>
   inline operator point<real>(void) const
   {
      return point<real>(r,0,z);
   }
};

}  // metamesh



// =============================================================================
// 3d cylindrical
// =============================================================================

namespace metamesh {

template<class real>
class cylindrical<3,real> {
public:

   // dimension, value_t
   static const std::size_t dimension = 3;
   using value_t = real;

   // coordinates
   union { real r, radius, s; };
   union { real t, theta; };
   real z;

   // default
   inline explicit cylindrical(void) { }

   // cylindrical(r,t,z)
   inline explicit cylindrical(const real &_r, const real &_t, const real &_z) :
      r(_r), t(_t), z(_z)
   { }

   // value
   inline real &value(const component<0>) { return r; }
   inline real &value(const component<1>) { return t; }
   inline real &value(const component<2>) { return z; }

   // value - const
   inline const real &value(const component<0>) const { return r; }
   inline const real &value(const component<1>) const { return t; }
   inline const real &value(const component<2>) const { return z; }

   // label
   static inline const char *label(const component<0>) { return "r"; }
   static inline const char *label(const component<1>) { return "t"; }
   static inline const char *label(const component<2>) { return "z"; }

   // conversion to point<real>
   inline operator point<real>(void) const
   {
      return point<real>(
         r*std::cos(t),
         r*std::sin(t),
         z
      );
   }
};

}  // metamesh



// =============================================================================
// 3d spherical
// =============================================================================

namespace metamesh {

template<class real>
class spherical<3,real> {
public:

   // dimension, value_t
   static const std::size_t dimension = 3;
   using value_t = real;

   // coordinates
   union { real r, radius, s; };
   union { real t, theta; };
   union { real p, phi; };

   // default
   inline explicit spherical(void) { }

   // spherical(r,t,p)
   inline explicit spherical(const real &_r, const real &_t, const real &_p) :
      r(_r), t(_t), p(_p)
   { }

   // value
   inline real &value(const component<0>) { return r; }
   inline real &value(const component<1>) { return t; }
   inline real &value(const component<2>) { return p; }

   // value - const
   inline const real &value(const component<0>) const { return r; }
   inline const real &value(const component<1>) const { return t; }
   inline const real &value(const component<2>) const { return p; }

   // label
   static inline const char *label(const component<0>) { return "r"; }
   static inline const char *label(const component<1>) { return "t"; }
   static inline const char *label(const component<2>) { return "p"; }

   // conversion to point<real>
   inline operator point<real>(void) const
   {
      return point<real>(
         r*std::cos(t)*std::sin(p),
         r*std::sin(t)*std::sin(p),
         r*std::cos(p)
      );
   }
};

}  // metamesh



// =============================================================================
// Dimension
// =============================================================================

namespace metamesh {

   // cartesian
   template<class real>
   const std::size_t metamesh::cartesian  <0,real>::dimension;
   template<class real>
   const std::size_t metamesh::cartesian  <1,real>::dimension;
   template<class real>
   const std::size_t metamesh::cartesian  <2,real>::dimension;
   template<class real>
   const std::size_t metamesh::cartesian  <3,real>::dimension;

   // polar
   template<class real>
   const std::size_t metamesh::polar      <2,real>::dimension;

   // cylindrical
   template<class real>
   const std::size_t metamesh::cylindrical<2,real>::dimension;
   template<class real>
   const std::size_t metamesh::cylindrical<3,real>::dimension;

   // spherical
   template<class real>
   const std::size_t metamesh::spherical  <3,real>::dimension;

}  // metamesh

#endif
