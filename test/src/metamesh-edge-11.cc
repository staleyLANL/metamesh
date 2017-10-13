
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<zero  <   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      g1((tup),flow<0>());
   edge<zero  <   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      g2((tup),flow<1>(1.2f));
   edge<zero  <   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      g3((tup),flow<2>(1.2f,3.4f));
   edge<zero  <   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      g4((tup),flow<3>(1.2f,3.4f,5.6f));
   edge<zero  <   node<polar      <2,double>, ijk<2> > > , flow<2> >
      g5((tup),flow<2>(1.2f,3.4f));
   edge<zero  <   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      g6((tup),flow<2>(1.2f,3.4f));
   edge<zero  <   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      g7((tup),flow<3>(1.2f,3.4f,5.6f));
   edge<zero  <   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      g8((tup),flow<3>(1.2f,3.4f,5.6f));
   print(g1);  print(g2);  print(g3);  print(g4);
   print(g5);  print(g6);  print(g7);  print(g8);
   print();
}
