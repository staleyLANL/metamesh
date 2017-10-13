
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // ------------------------
   // 3d spherical
   // ------------------------

   print("spherical<3>");
   print(metamesh::spherical<3>::dimension);
   print(sizeof(metamesh::spherical<3>::value_t));
   print();

   using coord = metamesh::spherical<3>;
   coord a;
   coord b(1.2, 3.4, 5.6);
   const coord c = b;
   print(metamesh::point<>(b));

   print(b.r), print(b.radius), print(b.s);
   print(b.t), print(b.theta);
   print(b.p), print(b.phi);
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

   print(metamesh::spherical<3>::label(metamesh::component<0>()));
   print(metamesh::spherical<3>::label(metamesh::component<1>()));
   print(metamesh::spherical<3>::label(metamesh::component<2>()));
}
