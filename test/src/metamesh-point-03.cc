
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   metamesh::point<> a(1,2,3);
   metamesh::point<> b(4,5,6);
   metamesh::point<> c(b);

   // ==, !=
   print(a == b);
   print(a != b);
   print(b == c);
   print(b != c);
   print();

   // real*point, point/real
   print(10.0*a);
   print(a/10.0);
   print();

   // +=, *=, /=
   a += b;    print(a);
   c *= 2.0;  print(c);
   c /= 2.0;  print(c);
   print();

   // u, v
   metamesh::point<> u(1,2,3);
   metamesh::point<> v(4,5,6);

   // dot, cross, +, -
   print(dot(u,v));
   print(cross(u,v));
   print(u+v);
   print(u-v);
   print();

   // mod2, mod
   print(mod2(u));
   print(mod(u));
   print();

   // <<
   std::cout << v << std::endl;
}
