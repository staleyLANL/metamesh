
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // ------------------------
   // 2d polar
   // ------------------------

   print("polar<2>");
   print(metamesh::polar<2>::dimension);
   print(sizeof(metamesh::polar<2>::value_t));
   print();

   using coord = metamesh::polar<2>;
   coord a;
   coord b(1.2, 3.4);
   const coord c = b;
   print(metamesh::point<>(b));

   print(b.r), print(b.radius), print(b.s);
   print(b.t), print(b.theta);
   print();

   print(b.value(metamesh::component<0>()));
   print(b.value(metamesh::component<1>()));
   print(c.value(metamesh::component<0>()));
   print(c.value(metamesh::component<1>()));
   print(c.label(metamesh::component<0>()));
   print(c.label(metamesh::component<1>()));
   print();

   print(metamesh::polar<2>::label(metamesh::component<0>()));
   print(metamesh::polar<2>::label(metamesh::component<1>()));
}
