
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<two   <   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      i1((tup,1,2),flow<0>());
   edge<two   <   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      i2((tup,1,2),flow<1>(1.2f));
   edge<two   <   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      i3((tup,1,2),flow<2>(1.2f,3.4f));
   edge<two   <   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      i4((tup,1,2),flow<3>(1.2f,3.4f,5.6f));
   edge<two   <   node<polar      <2,double>, ijk<2> > > , flow<2> >
      i5((tup,1,2),flow<2>(1.2f,3.4f));
   edge<two   <   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      i6((tup,1,2),flow<2>(1.2f,3.4f));
   edge<two   <   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      i7((tup,1,2),flow<3>(1.2f,3.4f,5.6f));
   edge<two   <   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      i8((tup,1,2),flow<3>(1.2f,3.4f,5.6f));
   print(i1);  print(i2);  print(i3);  print(i4);
   print(i5);  print(i6);  print(i7);  print(i8);
   print();
}
