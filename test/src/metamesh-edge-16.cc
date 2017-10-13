
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<five  <   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      l1((tup,1,2,3,4,5),flow<0>());
   edge<five  <   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      l2((tup,1,2,3,4,5),flow<1>(1.2f));
   edge<five  <   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      l3((tup,1,2,3,4,5),flow<2>(1.2f,3.4f));
   edge<five  <   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      l4((tup,1,2,3,4,5),flow<3>(1.2f,3.4f,5.6f));
   edge<five  <   node<polar      <2,double>, ijk<2> > > , flow<2> >
      l5((tup,1,2,3,4,5),flow<2>(1.2f,3.4f));
   edge<five  <   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      l6((tup,1,2,3,4,5),flow<2>(1.2f,3.4f));
   edge<five  <   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      l7((tup,1,2,3,4,5),flow<3>(1.2f,3.4f,5.6f));
   edge<five  <   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      l8((tup,1,2,3,4,5),flow<3>(1.2f,3.4f,5.6f));
   print(l1);  print(l2);  print(l3);  print(l4);
   print(l5);  print(l6);  print(l7);  print(l8);
   print();
}
