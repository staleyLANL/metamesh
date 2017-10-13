
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using namespace metamesh;
   edge<one   <   node<cartesian  <0,float >, ijk<0> > > , flow<0> >
      h1((tup,1),flow<0>());
   edge<one   <   node<cartesian  <1,double>, ijk<1> > > , flow<1> >
      h2((tup,1),flow<1>(1.2f));
   edge<one   <   node<cartesian  <2,quad  >, ijk<2> > > , flow<2> >
      h3((tup,1),flow<2>(1.2f,3.4f));
   edge<one   <   node<cartesian  <3,float >, ijk<3> > > , flow<3> >
      h4((tup,1),flow<3>(1.2f,3.4f,5.6f));
   edge<one   <   node<polar      <2,double>, ijk<2> > > , flow<2> >
      h5((tup,1),flow<2>(1.2f,3.4f));
   edge<one   <   node<cylindrical<2,quad  >, ijk<2> > > , flow<2> >
      h6((tup,1),flow<2>(1.2f,3.4f));
   edge<one   <   node<cylindrical<3,float >, ijk<3> > > , flow<3> >
      h7((tup,1),flow<3>(1.2f,3.4f,5.6f));
   edge<one   <   node<spherical  <3,double>, ijk<3> > > , flow<3> >
      h8((tup,1),flow<3>(1.2f,3.4f,5.6f));
   print(h1);  print(h2);  print(h3);  print(h4);
   print(h5);  print(h6);  print(h7);  print(h8);
   print();
}
