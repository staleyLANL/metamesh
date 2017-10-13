
#include "metamesh.h"

// sametype
template<class A, class B>
class sametype      { public: static const bool value; };
template<class T>
class sametype<T,T> { public: static const bool value; };

template<class A, class B>
const bool sametype<A,B>::value = false;
template<class T>
const bool sametype<T,T>::value = true;

// same
template<class A, class B>
inline void same(void)
{
   metamesh::print(sametype<A,B>::value);
}

// main
int main(void)
{
   // Illustrate some empty "coordinate system" classes
   // qqq I later moved these to metamesh-coord.h, so maybe I should
   // move this test stuff as well.

   same< metamesh::cartesian  <0,double>, metamesh::cartesian  <0> >();
   same< metamesh::cartesian  <1,double>, metamesh::cartesian  <1> >();
   same< metamesh::cartesian  <2,double>, metamesh::cartesian  <2> >();
   same< metamesh::cartesian  <3,double>, metamesh::cartesian  <3> >();
   same< metamesh::polar      <2,double>, metamesh::polar      <2> >();
   same< metamesh::cylindrical<2,double>, metamesh::cylindrical<2> >();
   same< metamesh::cylindrical<3,double>, metamesh::cylindrical<3> >();
   same< metamesh::spherical  <3,double>, metamesh::spherical  <3> >();

   same< metamesh::polar      <2>, metamesh::polar      <> >();
   same< metamesh::cylindrical<3>, metamesh::cylindrical<> >();
   same< metamesh::spherical  <3>, metamesh::spherical  <> >();
}
