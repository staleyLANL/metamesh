
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<eight <   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      o1((tup,1,2,3,4,5,6,7,8),flow<0>());
   edge<eight <   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      o2((tup,1,2,3,4,5,6,7,8),flow<1>(1.2f));
   edge<eight <   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      o3((tup,1,2,3,4,5,6,7,8),flow<2>(1.2f,3.4f));
   edge<eight <   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      o4((tup,1,2,3,4,5,6,7,8),flow<3>(1.2f,3.4f,5.6f));
   edge<eight <   node<polar      <2,double>, ijk<2> > > , flow<2> >
      o5((tup,1,2,3,4,5,6,7,8),flow<2>(1.2f,3.4f));
   edge<eight <   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      o6((tup,1,2,3,4,5,6,7,8),flow<2>(1.2f,3.4f));
   edge<eight <   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      o7((tup,1,2,3,4,5,6,7,8),flow<3>(1.2f,3.4f,5.6f));
   edge<eight <   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      o8((tup,1,2,3,4,5,6,7,8),flow<3>(1.2f,3.4f,5.6f));
   print(o1);  print(o2);  print(o3);  print(o4);
   print(o5);  print(o6);  print(o7);  print(o8);
   print();
}
