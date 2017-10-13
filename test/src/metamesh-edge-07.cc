
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<tuple < 2,node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      c1((tup,1,2),flow<0>());
   edge<tuple < 2,node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      c2((tup,1,2),flow<1>(1.2f));
   edge<tuple < 2,node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      c3((tup,1,2),flow<2>(1.2f,3.4f));
   edge<tuple < 2,node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      c4((tup,1,2),flow<3>(1.2f,3.4f,5.6f));
   edge<tuple < 2,node<polar      <2,double>, ijk<2> > > , flow<2> >
      c5((tup,1,2),flow<2>(1.2f,3.4f));
   edge<tuple < 2,node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      c6((tup,1,2),flow<2>(1.2f,3.4f));
   edge<tuple < 2,node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      c7((tup,1,2),flow<3>(1.2f,3.4f,5.6f));
   edge<tuple < 2,node<spherical  <3,double>, ijk<3> > > , flow<3> >
      c8((tup,1,2),flow<3>(1.2f,3.4f,5.6f));
   print(c1);  print(c2);  print(c3);  print(c4);
   print(c5);  print(c6);  print(c7);  print(c8);
   print();
}
