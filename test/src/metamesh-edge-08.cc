
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<tuple < 4,node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      d1((tup,1,2,3,4),flow<0>());
   edge<tuple < 4,node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      d2((tup,1,2,3,4),flow<1>(1.2f));
   edge<tuple < 4,node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      d3((tup,1,2,3,4),flow<2>(1.2f,3.4f));
   edge<tuple < 4,node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      d4((tup,1,2,3,4),flow<3>(1.2f,3.4f,5.6f));
   edge<tuple < 4,node<polar      <2,double>, ijk<2> > > , flow<2> >
      d5((tup,1,2,3,4),flow<2>(1.2f,3.4f));
   edge<tuple < 4,node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      d6((tup,1,2,3,4),flow<2>(1.2f,3.4f));
   edge<tuple < 4,node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      d7((tup,1,2,3,4),flow<3>(1.2f,3.4f,5.6f));
   edge<tuple < 4,node<spherical  <3,double>, ijk<3> > > , flow<3> >
      d8((tup,1,2,3,4),flow<3>(1.2f,3.4f,5.6f));
   print(d1);  print(d2);  print(d3);  print(d4);
   print(d5);  print(d6);  print(d7);  print(d8);
   print();
}
