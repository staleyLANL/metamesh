
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<twelve<   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      s1((tup,1,2,3,4,5,6,7,8,9,10,11,12),flow<0>());
   edge<twelve<   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      s2((tup,1,2,3,4,5,6,7,8,9,10,11,12),flow<1>(1.2f));
   edge<twelve<   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      s3((tup,1,2,3,4,5,6,7,8,9,10,11,12),flow<2>(1.2f,3.4f));
   edge<twelve<   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      s4((tup,1,2,3,4,5,6,7,8,9,10,11,12),flow<3>(1.2f,3.4f,5.6f));
   edge<twelve<   node<polar      <2,double>, ijk<2> > > , flow<2> >
      s5((tup,1,2,3,4,5,6,7,8,9,10,11,12),flow<2>(1.2f,3.4f));
   edge<twelve<   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      s6((tup,1,2,3,4,5,6,7,8,9,10,11,12),flow<2>(1.2f,3.4f));
   edge<twelve<   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      s7((tup,1,2,3,4,5,6,7,8,9,10,11,12),flow<3>(1.2f,3.4f,5.6f));
   edge<twelve<   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      s8((tup,1,2,3,4,5,6,7,8,9,10,11,12),flow<3>(1.2f,3.4f,5.6f));
   print(s1);  print(s2);  print(s3);  print(s4);
   print(s5);  print(s6);  print(s7);  print(s8);
   print();
}
