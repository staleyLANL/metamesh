
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // ------------------------
   // 3d cartesian
   // ------------------------

   print("cartesian<3>");
   print(metamesh::cartesian<3>::dimension);
   print(sizeof(metamesh::cartesian<3>::value_t));
   print();

   using coord = metamesh::cartesian<3>;
   coord a;
   coord b(1.2, 3.4, 5.6);
   const coord c = b;
   print(metamesh::point<>(b));

   print(b.x);
   print(b.y);
   print(b.z);
   print();

   print(b.value(metamesh::component<0>()));
   print(b.value(metamesh::component<1>()));
   print(b.value(metamesh::component<2>()));
   print(c.value(metamesh::component<0>()));
   print(c.value(metamesh::component<1>()));
   print(c.value(metamesh::component<2>()));
   print(c.label(metamesh::component<0>()));
   print(c.label(metamesh::component<1>()));
   print(c.label(metamesh::component<2>()));
   print();

   print(metamesh::cartesian<3>::label(metamesh::component<0>()));
   print(metamesh::cartesian<3>::label(metamesh::component<1>()));
   print(metamesh::cartesian<3>::label(metamesh::component<2>()));
}
