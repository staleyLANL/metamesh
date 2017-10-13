
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<eleven<   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      r1((tup,1,2,3,4,5,6,7,8,9,10,11),flow<0>());
   edge<eleven<   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      r2((tup,1,2,3,4,5,6,7,8,9,10,11),flow<1>(1.2f));
   edge<eleven<   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      r3((tup,1,2,3,4,5,6,7,8,9,10,11),flow<2>(1.2f,3.4f));
   edge<eleven<   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      r4((tup,1,2,3,4,5,6,7,8,9,10,11),flow<3>(1.2f,3.4f,5.6f));
   edge<eleven<   node<polar      <2,double>, ijk<2> > > , flow<2> >
      r5((tup,1,2,3,4,5,6,7,8,9,10,11),flow<2>(1.2f,3.4f));
   edge<eleven<   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      r6((tup,1,2,3,4,5,6,7,8,9,10,11),flow<2>(1.2f,3.4f));
   edge<eleven<   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      r7((tup,1,2,3,4,5,6,7,8,9,10,11),flow<3>(1.2f,3.4f,5.6f));
   edge<eleven<   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      r8((tup,1,2,3,4,5,6,7,8,9,10,11),flow<3>(1.2f,3.4f,5.6f));
   print(r1);  print(r2);  print(r3);  print(r4);
   print(r5);  print(r6);  print(r7);  print(r8);
   print();
}
