
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // ------------------------
   // 1d cartesian
   // ------------------------

   print("cartesian<1>");
   print(metamesh::cartesian<1>::dimension);
   print(sizeof(metamesh::cartesian<1>::value_t));
   print();

   using coord = metamesh::cartesian<1>;
   coord a;
   coord b(1.2);
   const coord c = b;
   print(metamesh::point<>(b));

   print(b.x);
   print();

   print(b.value(metamesh::component<0>()));
   print(c.value(metamesh::component<0>()));
   print(c.label(metamesh::component<0>()));
   print();

   print(metamesh::cartesian<1>::label(metamesh::component<0>()));
}
