
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<tuple < 1,node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      b1((tup,1),flow<0>());
   edge<tuple < 1,node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      b2((tup,1),flow<1>(1.2f));
   edge<tuple < 1,node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      b3((tup,1),flow<2>(1.2f,3.4f));
   edge<tuple < 1,node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      b4((tup,1),flow<3>(1.2f,3.4f,5.6f));
   edge<tuple < 1,node<polar      <2,double>, ijk<2> > > , flow<2> >
      b5((tup,1),flow<2>(1.2f,3.4f));
   edge<tuple < 1,node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      b6((tup,1),flow<2>(1.2f,3.4f));
   edge<tuple < 1,node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      b7((tup,1),flow<3>(1.2f,3.4f,5.6f));
   edge<tuple < 1,node<spherical  <3,double>, ijk<3> > > , flow<3> >
      b8((tup,1),flow<3>(1.2f,3.4f,5.6f));
   print(b1);  print(b2);  print(b3);  print(b4);
   print(b5);  print(b6);  print(b7);  print(b8);
   print();
}
