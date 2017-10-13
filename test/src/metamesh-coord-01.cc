
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // ------------------------
   // basics
   // ------------------------

   // component
   print("component size");
   print(sizeof(metamesh::component<0>));
   print();

   // cartesian
   print("cartesian sizes");
   print(sizeof(metamesh::cartesian  <0       >));
   print(sizeof(metamesh::cartesian  <0,double>));
   print(sizeof(metamesh::cartesian  <1       >));
   print(sizeof(metamesh::cartesian  <1,double>));
   print(sizeof(metamesh::cartesian  <2       >));
   print(sizeof(metamesh::cartesian  <2,double>));
   print(sizeof(metamesh::cartesian  <3       >));
   print(sizeof(metamesh::cartesian  <3,double>));
   print();

   // polar
   print("polar sizes");
   print(sizeof(metamesh::polar      <        >));
   print(sizeof(metamesh::polar      <2       >));
   print(sizeof(metamesh::polar      <2,double>));
   print();

   // cylindrical
   print("cylindrical sizes");
   print(sizeof(metamesh::cylindrical<        >));
   print(sizeof(metamesh::cylindrical<2       >));
   print(sizeof(metamesh::cylindrical<2,double>));
   print(sizeof(metamesh::cylindrical<3       >));
   print(sizeof(metamesh::cylindrical<3,double>));
   print();

   // spherical
   print("spherical sizes");
   print(sizeof(metamesh::spherical  <        >));
   print(sizeof(metamesh::spherical  <3       >));
   print(sizeof(metamesh::spherical  <3,double>));
   print();
}
