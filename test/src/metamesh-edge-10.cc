
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<tuple <16,node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      f1((tup,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16),
         flow<0>());
   edge<tuple <16,node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      f2((tup,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16),
         flow<1>(1.2f));
   edge<tuple <16,node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      f3((tup,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16),
         flow<2>(1.2f,3.4f));
   edge<tuple <16,node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      f4((tup,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16),
         flow<3>(1.2f,3.4f,5.6f));
   edge<tuple <16,node<polar      <2,double>, ijk<2> > > , flow<2> >
      f5((tup,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16),
         flow<2>(1.2f,3.4f));
   edge<tuple <16,node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      f6((tup,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16),
         flow<2>(1.2f,3.4f));
   edge<tuple <16,node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      f7((tup,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16),
         flow<3>(1.2f,3.4f,5.6f));
   edge<tuple <16,node<spherical  <3,double>, ijk<3> > > , flow<3> >
      f8((tup,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16),
         flow<3>(1.2f,3.4f,5.6f));
   print(f1);  print(f2);  print(f3);  print(f4);
   print(f5);  print(f6);  print(f7);  print(f8);
   print();
}
