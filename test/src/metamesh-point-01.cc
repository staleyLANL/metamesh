
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   metamesh::point<> a;
   metamesh::point<int> b(7,11,13);
   metamesh::point<double> c(b);
   metamesh::point<double> d;

   d = c;
   d = b;
   a(2,3,5);

   (void)a.x;  (void)b.x;  (void)c.x;
   (void)a.y;  (void)b.y;  (void)c.y;
   (void)a.z;  (void)b.z;  (void)c.z;

   print(a);
   print(b);
   print(c);
   print(d);
}

/*
// operator==
template<class real>
inline bool operator==(
   const metamesh::point<real> &a,
   const metamesh::point<real> &b
)

// operator!=
template<class real>
inline bool operator!=(
   const metamesh::point<real> &a,
   const metamesh::point<real> &b
)



// real*point
template<class real>
inline metamesh::point<real> operator*(
   const real &c,
   const metamesh::point<real> &u
)

// point/real
template<class real>
inline metamesh::point<real> operator/(
   const metamesh::point<real> &u,
   const real &c
)



// point += point
template<class real>
inline metamesh::point<real> &operator+=(
   metamesh::point<real> &u,
   const metamesh::point<real> &v
)



// point *= real
template<class real>
inline metamesh::point<real> &operator*=(
   metamesh::point<real> &u,
   const real &c
)

// point /= real
template<class real>
inline metamesh::point<real> &operator/=(
   metamesh::point<real> &u,
   const real &c
)



// dot(u,v)
template<class real>
inline real dot(
   const metamesh::point<real> &u,
   const metamesh::point<real> &v
)

// cross(u,v)
template<class real>
inline metamesh::point<real> cross(
   const metamesh::point<real> &u,
   const metamesh::point<real> &v
)



// u+v
template<class real>
inline metamesh::point<real> operator+(
   const metamesh::point<real> &u,
   const metamesh::point<real> &v
)

// u-v
template<class real>
inline metamesh::point<real> operator-(
   const metamesh::point<real> &u,
   const metamesh::point<real> &v
)



// mod2(u) ("mod squared")
// Useful in some contexts, to avoid computing square roots
template<class real>
inline real mod2(const metamesh::point<real> &u)

// mod(u)
template<class real>
inline real mod(const metamesh::point<real> &u)



// ostream << point
template<class real>
inline std::ostream &operator<<(
   std::ostream &s,
   const metamesh::point<real> &obj
)
*/
