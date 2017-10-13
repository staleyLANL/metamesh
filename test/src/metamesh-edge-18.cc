
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<seven <   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      n1((tup,1,2,3,4,5,6,7),flow<0>());
   edge<seven <   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      n2((tup,1,2,3,4,5,6,7),flow<1>(1.2f));
   edge<seven <   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      n3((tup,1,2,3,4,5,6,7),flow<2>(1.2f,3.4f));
   edge<seven <   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      n4((tup,1,2,3,4,5,6,7),flow<3>(1.2f,3.4f,5.6f));
   edge<seven <   node<polar      <2,double>, ijk<2> > > , flow<2> >
      n5((tup,1,2,3,4,5,6,7),flow<2>(1.2f,3.4f));
   edge<seven <   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      n6((tup,1,2,3,4,5,6,7),flow<2>(1.2f,3.4f));
   edge<seven <   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      n7((tup,1,2,3,4,5,6,7),flow<3>(1.2f,3.4f,5.6f));
   edge<seven <   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      n8((tup,1,2,3,4,5,6,7),flow<3>(1.2f,3.4f,5.6f));
   print(n1);  print(n2);  print(n3);  print(n4);
   print(n5);  print(n6);  print(n7);  print(n8);
   print();
}
