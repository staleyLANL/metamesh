
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<four  <   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      k1((tup,1,2,3,4),flow<0>());
   edge<four  <   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      k2((tup,1,2,3,4),flow<1>(1.2f));
   edge<four  <   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      k3((tup,1,2,3,4),flow<2>(1.2f,3.4f));
   edge<four  <   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      k4((tup,1,2,3,4),flow<3>(1.2f,3.4f,5.6f));
   edge<four  <   node<polar      <2,double>, ijk<2> > > , flow<2> >
      k5((tup,1,2,3,4),flow<2>(1.2f,3.4f));
   edge<four  <   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      k6((tup,1,2,3,4),flow<2>(1.2f,3.4f));
   edge<four  <   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      k7((tup,1,2,3,4),flow<3>(1.2f,3.4f,5.6f));
   edge<four  <   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      k8((tup,1,2,3,4),flow<3>(1.2f,3.4f,5.6f));
   print(k1);  print(k2);  print(k3);  print(k4);
   print(k5);  print(k6);  print(k7);  print(k8);
   print();
}
