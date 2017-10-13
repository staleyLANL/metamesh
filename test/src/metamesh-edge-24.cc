
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<some  <   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      t1((tup,  2,3,4,5,6,7,8,9,10,   12),flow<0>());
   edge<some  <   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      t2((tup,1,  3,4,5,6,7,8,9,   11,12),flow<1>(1.2f));
   edge<some  <   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      t3((tup,1,2,  4,5,6,7,8,     11,12),flow<2>(1.2f,3.4f));
   edge<some  <   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      t4((tup,1,2,3,  5,6,7,  9,10,   12),flow<3>(1.2f,3.4f,5.6f));
   edge<some  <   node<polar      <2,double>, ijk<2> > > , flow<2> >
      t5((tup,1,2,3,    6,  8,9,10,11   ),flow<2>(1.2f,3.4f));
   edge<some  <   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      t6((tup,1,2,  4,5,  7,8,9,10,11,12),flow<2>(1.2f,3.4f));
   edge<some  <   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      t7((tup,1,  3,4,5,6,  8,9,10,11,12),flow<3>(1.2f,3.4f,5.6f));
   edge<some  <   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      t8((tup,  2,3,4,5,6,7,  9,10,11,12),flow<3>(1.2f,3.4f,5.6f));
   print(t1);  print(t2);  print(t3);  print(t4);
   print(t5);  print(t6);  print(t7);  print(t8);
   print();
}
