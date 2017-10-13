
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<nine  <   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      p1((tup,1,2,3,4,5,6,7,8,9),flow<0>());
   edge<nine  <   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      p2((tup,1,2,3,4,5,6,7,8,9),flow<1>(1.2f));
   edge<nine  <   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      p3((tup,1,2,3,4,5,6,7,8,9),flow<2>(1.2f,3.4f));
   edge<nine  <   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      p4((tup,1,2,3,4,5,6,7,8,9),flow<3>(1.2f,3.4f,5.6f));
   edge<nine  <   node<polar      <2,double>, ijk<2> > > , flow<2> >
      p5((tup,1,2,3,4,5,6,7,8,9),flow<2>(1.2f,3.4f));
   edge<nine  <   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      p6((tup,1,2,3,4,5,6,7,8,9),flow<2>(1.2f,3.4f));
   edge<nine  <   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      p7((tup,1,2,3,4,5,6,7,8,9),flow<3>(1.2f,3.4f,5.6f));
   edge<nine  <   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      p8((tup,1,2,3,4,5,6,7,8,9),flow<3>(1.2f,3.4f,5.6f));
   print(p1);  print(p2);  print(p3);  print(p4);
   print(p5);  print(p6);  print(p7);  print(p8);
   print();
}
