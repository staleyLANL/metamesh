
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   assert(sizeof(metamesh::quad) == sizeof(metamesh::pi));
   assert(sizeof(metamesh::quad) == sizeof(metamesh::twopi));

   // pi, twopi
   print(metamesh::pi);
   print(metamesh::twopi);

   // fyi; should be small
   print(metamesh::twopi - 2*metamesh::pi);

   // deg2rad, rad2deg
   std::cout << "pi/180 is about " << metamesh::deg2rad << std::endl;
   std::cout << "180/pi is about " << metamesh::rad2deg << std::endl;

   // some differences
   print(metamesh::pi - float (metamesh::pi));
   print(metamesh::pi - double(metamesh::pi));
   print(metamesh::twopi - float (metamesh::twopi));
   print(metamesh::twopi - double(metamesh::twopi));
   print(metamesh::deg2rad - float (metamesh::deg2rad));
   print(metamesh::deg2rad - double(metamesh::deg2rad));
   print(metamesh::rad2deg - float (metamesh::rad2deg));
   print(metamesh::rad2deg - double(metamesh::rad2deg));
}
