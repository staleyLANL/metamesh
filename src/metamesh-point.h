/* -*- C++ -*- */

#ifndef METAMESH_POINT
#define METAMESH_POINT

// This file provides the "point" class and related functionality. Points
// represent 3d coordinates (x,y,z) in metamesh's interface to the kip ray
// tracer. We avoid using kip's point<real> here, so that metamesh is more
// independent of kip. More specifically, some (not all) of metamesh's kip-
// related activities don't require #including kip; our independent point
// class helps keep it that way.



// =============================================================================
// point
// 3d only. We don't support 0d, 1d or 2d points, because, for our present
// purposes, metamesh doesn't need them.
// =============================================================================

namespace metamesh {

template<
   #ifdef METAMESH_NO_DEFAULT
      class real
   #else
      class real = default_real_t
   #endif
>
class point {
public:
   // data
   real x, y, z;

   // point()
   inline explicit point(void)
   { }

   // point(x,y,z)
   inline explicit point(const real &_x, const real &_y, const real &_z) :
      x(_x), y(_y), z(_z)
   { }

   // construction from point<FROM>
   template<class FROM>
   inline explicit point(const point<FROM> &from) :
      x(real(from.x)), y(real(from.y)), z(real(from.z))
   { }

   // assignment from point<FROM>
   template<class FROM>
   inline point &operator=(const point<FROM> &from)
   {
      x = real(from.x);
      y = real(from.y);
      z = real(from.z);
      return *this;
   }

   // operator()(x,y,z)
   // Convenient "assignment" from (x,y,z).
   // Perhaps a bit odd, syntactically speaking.
   inline point &operator()(const real &_x, const real &_y, const real &_z)
   {
      x = _x;
      y = _y;
      z = _z;
      return *this;
   }


   // ------------------------
   // If the kip library is
   // present, construct from
   // and convert to kip point
   // ------------------------

#if defined(KIP_RENDERER)
   // construct from kip::point<T>
   template<class T>
   inline explicit point(const ::kip::point<T> &from) :
      x(real(from.x)), y(real(from.y)), z(real(from.z))
   { }

   // convert to kip::point<T>
   template<class T>
   inline operator ::kip::point<T>(void) const
   {
      return ::kip::point<T>(T(x), T(y), T(z));
   }
#endif

};

}  // metamesh



// =============================================================================
// Functions for point
// Note: point's role in metamesh is limited, and it isn't intended for general
// use. Therefore, we provide only the minimal functionality metamesh needs.
// =============================================================================

namespace metamesh {

// operator==
template<class real>
inline bool operator==(
   const metamesh::point<real> &a,
   const metamesh::point<real> &b
) {
   return a.x == b.x && a.y == b.y && a.z == b.z;
}

// operator!=
template<class real>
inline bool operator!=(
   const metamesh::point<real> &a,
   const metamesh::point<real> &b
) {
   return !(a == b);
}



// real*point
template<class real>
inline metamesh::point<real> operator*(
   const real &c,
   const metamesh::point<real> &u
) {
   return metamesh::point<real>(c*u.x, c*u.y, c*u.z);
}

// point/real
template<class real>
inline metamesh::point<real> operator/(
   const metamesh::point<real> &u,
   const real &c
) {
   return metamesh::point<real>(u.x/c, u.y/c, u.z/c);
}



// point += point
template<class real>
inline metamesh::point<real> &operator+=(
   metamesh::point<real> &u,
   const metamesh::point<real> &v
) {
   u.x += v.x;
   u.y += v.y;
   u.z += v.z;
   return u;
}



// point *= real
template<class real>
inline metamesh::point<real> &operator*=(
   metamesh::point<real> &u,
   const real &c
) {
   u.x *= c;
   u.y *= c;
   u.z *= c;
   return u;
}

// point /= real
template<class real>
inline metamesh::point<real> &operator/=(
   metamesh::point<real> &u,
   const real &c
) {
   u.x /= c;
   u.y /= c;
   u.z /= c;
   return u;
}



// dot(u,v)
template<class real>
inline real dot(
   const metamesh::point<real> &u,
   const metamesh::point<real> &v
) {
   return u.x*v.x + u.y*v.y + u.z*v.z;
}

// cross(u,v)
template<class real>
inline metamesh::point<real> cross(
   const metamesh::point<real> &u,
   const metamesh::point<real> &v
) {
   return metamesh::point<real>(
      u.y*v.z - u.z*v.y,
      u.z*v.x - u.x*v.z,
      u.x*v.y - u.y*v.x
   );
}



// u+v
template<class real>
inline metamesh::point<real> operator+(
   const metamesh::point<real> &u,
   const metamesh::point<real> &v
) {
   return metamesh::point<real>(u.x+v.x, u.y+v.y, u.z+v.z);
}

// u-v
template<class real>
inline metamesh::point<real> operator-(
   const metamesh::point<real> &u,
   const metamesh::point<real> &v
) {
   return metamesh::point<real>(u.x-v.x, u.y-v.y, u.z-v.z);
}



// mod2(u) ("mod squared")
// Useful in some contexts, to avoid computing square roots
template<class real>
inline real mod2(const metamesh::point<real> &u)
{
   return dot(u,u);
}

// mod(u)
template<class real>
inline real mod(const metamesh::point<real> &u)
{
   return sqrt(mod2(u));
}

// normalize(u)
// Normalize the point<>; except return (0,0,0) if modulus is 0
template<class real>
inline metamesh::point<real> normalize(const metamesh::point<real> &u)
{
   const real m = mod(u);
   return m != real(0) ? u/m : metamesh::point<real>(real(0), real(0), real(0));
}



// ostream << point
template<class real>
inline std::ostream &operator<<(
   std::ostream &s,
   const metamesh::point<real> &obj
) {
   return s << obj.x << ',' << obj.y << ',' << obj.z;
}

}  // metamesh

#endif
