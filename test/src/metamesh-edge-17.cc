
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<six   <   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      m1((tup,1,2,3,4,5,6),flow<0>());
   edge<six   <   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      m2((tup,1,2,3,4,5,6),flow<1>(1.2f));
   edge<six   <   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      m3((tup,1,2,3,4,5,6),flow<2>(1.2f,3.4f));
   edge<six   <   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      m4((tup,1,2,3,4,5,6),flow<3>(1.2f,3.4f,5.6f));
   edge<six   <   node<polar      <2,double>, ijk<2> > > , flow<2> >
      m5((tup,1,2,3,4,5,6),flow<2>(1.2f,3.4f));
   edge<six   <   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      m6((tup,1,2,3,4,5,6),flow<2>(1.2f,3.4f));
   edge<six   <   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      m7((tup,1,2,3,4,5,6),flow<3>(1.2f,3.4f,5.6f));
   edge<six   <   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      m8((tup,1,2,3,4,5,6),flow<3>(1.2f,3.4f,5.6f));
   print(m1);  print(m2);  print(m3);  print(m4);
   print(m5);  print(m6);  print(m7);  print(m8);
   print();
}
