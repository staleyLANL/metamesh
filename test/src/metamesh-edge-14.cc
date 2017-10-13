
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<three <   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      j1((tup,1,2,3),flow<0>());
   edge<three <   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      j2((tup,1,2,3),flow<1>(1.2f));
   edge<three <   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      j3((tup,1,2,3),flow<2>(1.2f,3.4f));
   edge<three <   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      j4((tup,1,2,3),flow<3>(1.2f,3.4f,5.6f));
   edge<three <   node<polar      <2,double>, ijk<2> > > , flow<2> >
      j5((tup,1,2,3),flow<2>(1.2f,3.4f));
   edge<three <   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      j6((tup,1,2,3),flow<2>(1.2f,3.4f));
   edge<three <   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      j7((tup,1,2,3),flow<3>(1.2f,3.4f,5.6f));
   edge<three <   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      j8((tup,1,2,3),flow<3>(1.2f,3.4f,5.6f));
   print(j1);  print(j2);  print(j3);  print(j4);
   print(j5);  print(j6);  print(j7);  print(j8);
   print();
}
