
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // ------------------------
   // dimensions
   // ------------------------

   print(metamesh::node<metamesh::cartesian  <0,double> >::dimension);
   print(metamesh::node<metamesh::cartesian  <1,double> >::dimension);
   print(metamesh::node<metamesh::cartesian  <2,double> >::dimension);
   print(metamesh::node<metamesh::cartesian  <3,double> >::dimension);
   print(metamesh::node<metamesh::polar      <2,double> >::dimension);
   print(metamesh::node<metamesh::cylindrical<2,double> >::dimension);
   print(metamesh::node<metamesh::cylindrical<3,double> >::dimension);
   print(metamesh::node<metamesh::spherical  <3,double> >::dimension);

   // ------------------------
   // sizes
   // ------------------------

   print(sizeof(metamesh::node<metamesh::cartesian  <0,double> >));
   print(sizeof(metamesh::node<metamesh::cartesian  <1,double> >));
   print(sizeof(metamesh::node<metamesh::cartesian  <2,double> >));
   print(sizeof(metamesh::node<metamesh::cartesian  <3,double> >));
   print(sizeof(metamesh::node<metamesh::polar      <2,double> >));
   print(sizeof(metamesh::node<metamesh::cylindrical<2,double> >));
   print(sizeof(metamesh::node<metamesh::cylindrical<3,double> >));
   print(sizeof(metamesh::node<metamesh::spherical  <3,double> >));
}
