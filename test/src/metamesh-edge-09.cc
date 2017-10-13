
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<tuple < 8,node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      e1((tup,1,2,3,4,5,6,7,8),flow<0>());
   edge<tuple < 8,node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      e2((tup,1,2,3,4,5,6,7,8),flow<1>(1.2f));
   edge<tuple < 8,node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      e3((tup,1,2,3,4,5,6,7,8),flow<2>(1.2f,3.4f));
   edge<tuple < 8,node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      e4((tup,1,2,3,4,5,6,7,8),flow<3>(1.2f,3.4f,5.6f));
   edge<tuple < 8,node<polar      <2,double>, ijk<2> > > , flow<2> >
      e5((tup,1,2,3,4,5,6,7,8),flow<2>(1.2f,3.4f));
   edge<tuple < 8,node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      e6((tup,1,2,3,4,5,6,7,8),flow<2>(1.2f,3.4f));
   edge<tuple < 8,node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      e7((tup,1,2,3,4,5,6,7,8),flow<3>(1.2f,3.4f,5.6f));
   edge<tuple < 8,node<spherical  <3,double>, ijk<3> > > , flow<3> >
      e8((tup,1,2,3,4,5,6,7,8),flow<3>(1.2f,3.4f,5.6f));
   print(e1);  print(e2);  print(e3);  print(e4);
   print(e5);  print(e6);  print(e7);  print(e8);
   print();
}
