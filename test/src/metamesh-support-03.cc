
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // ------------------------
   // 2d
   // ------------------------

   // nodes
   metamesh::node<metamesh::cartesian<2>> a(1,1);
   metamesh::node<metamesh::cartesian<2>> b(1.00000001,1.00000001);
   metamesh::node<metamesh::cartesian<2>> c(1.1,1.1);

   // near
   const double eps = 1e-12;
   print(metamesh::internal::near(a,b, 1.0,  eps));
   print(metamesh::internal::near(a,b, 1e6,  eps));
   print(metamesh::internal::near(a,c, 1.0,  eps));
   print(metamesh::internal::near(a,c, 1e12, eps));
   print();

   // distance
   double one, two;
   print(metamesh::internal::distance(a,b));
   print(one=metamesh::internal::distance(a,c));
   print(two=metamesh::internal::distance(b,c));
   print(one == two);  // not quite
   print();
}
