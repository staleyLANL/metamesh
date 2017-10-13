
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // ------------------------
   // 2d cartesian
   // ------------------------

   print("cartesian<2>");
   print(metamesh::cartesian<2>::dimension);
   print(sizeof(metamesh::cartesian<2>::value_t));
   print();

   using coord = metamesh::cartesian<2>;
   coord a;
   coord b(1.2, 3.4);
   const coord c = b;
   print(metamesh::point<>(b));

   print(b.x);
   print(b.y);
   print();

   print(b.value(metamesh::component<0>()));
   print(b.value(metamesh::component<1>()));
   print(c.value(metamesh::component<0>()));
   print(c.value(metamesh::component<1>()));
   print(c.label(metamesh::component<0>()));
   print(c.label(metamesh::component<1>()));
   print();

   print(metamesh::cartesian<2>::label(metamesh::component<0>()));
   print(metamesh::cartesian<2>::label(metamesh::component<1>()));
}
