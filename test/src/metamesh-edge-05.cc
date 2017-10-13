
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<tuple < 0,node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      a1((tup),flow<0>());
   edge<tuple < 0,node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      a2((tup),flow<1>(1.2f));
   edge<tuple < 0,node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      a3((tup),flow<2>(1.2f,3.4f));
   edge<tuple < 0,node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      a4((tup),flow<3>(1.2f,3.4f,5.6f));
   edge<tuple < 0,node<polar      <2,double>, ijk<2> > > , flow<2> >
      a5((tup),flow<2>(1.2f,3.4f));
   edge<tuple < 0,node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      a6((tup),flow<2>(1.2f,3.4f));
   edge<tuple < 0,node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      a7((tup),flow<3>(1.2f,3.4f,5.6f));
   edge<tuple < 0,node<spherical  <3,double>, ijk<3> > > , flow<3> >
      a8((tup),flow<3>(1.2f,3.4f,5.6f));
   print(a1);  print(a2);  print(a3);  print(a4);
   print(a5);  print(a6);  print(a7);  print(a8);
   print();
}
