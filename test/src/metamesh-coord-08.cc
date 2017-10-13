
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // ------------------------
   // 3d cylindrical
   // ------------------------

   print("cylindrical<3>");
   print(metamesh::cylindrical<3>::dimension);
   print(sizeof(metamesh::cylindrical<3>::value_t));
   print();

   using coord = metamesh::cylindrical<3>;
   coord a;
   coord b(1.2, 3.4, 5.6);
   const coord c = b;
   print(metamesh::point<>(b));

   print(b.r), print(b.radius), print(b.s);
   print(b.t), print(b.theta);
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

   print(metamesh::cylindrical<3>::label(metamesh::component<0>()));
   print(metamesh::cylindrical<3>::label(metamesh::component<1>()));
   print(metamesh::cylindrical<3>::label(metamesh::component<2>()));
}
