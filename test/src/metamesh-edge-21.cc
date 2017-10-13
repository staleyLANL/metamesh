
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<ten   <   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      q1((tup,1,2,3,4,5,6,7,8,9,10),flow<0>());
   edge<ten   <   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      q2((tup,1,2,3,4,5,6,7,8,9,10),flow<1>(1.2f));
   edge<ten   <   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      q3((tup,1,2,3,4,5,6,7,8,9,10),flow<2>(1.2f,3.4f));
   edge<ten   <   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      q4((tup,1,2,3,4,5,6,7,8,9,10),flow<3>(1.2f,3.4f,5.6f));
   edge<ten   <   node<polar      <2,double>, ijk<2> > > , flow<2> >
      q5((tup,1,2,3,4,5,6,7,8,9,10),flow<2>(1.2f,3.4f));
   edge<ten   <   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      q6((tup,1,2,3,4,5,6,7,8,9,10),flow<2>(1.2f,3.4f));
   edge<ten   <   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      q7((tup,1,2,3,4,5,6,7,8,9,10),flow<3>(1.2f,3.4f,5.6f));
   edge<ten   <   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      q8((tup,1,2,3,4,5,6,7,8,9,10),flow<3>(1.2f,3.4f,5.6f));
   print(q1);  print(q2);  print(q3);  print(q4);
   print(q5);  print(q6);  print(q7);  print(q8);
   print();
}
