
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // ------------------------
   // 0d cartesian
   // ------------------------

   print("cartesian<0>");
   print(metamesh::cartesian<0>::dimension);
   print(sizeof(metamesh::cartesian<0>::value_t));
   print();

   using coord = metamesh::cartesian<0>;
   coord a;
   coord b;
   const coord c = b;
   print(metamesh::point<>(b));
   (void)c;
}
