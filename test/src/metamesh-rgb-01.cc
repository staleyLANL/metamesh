
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   metamesh::rgb rgb1;
   metamesh::rgb rgb2(100);
   metamesh::rgb rgb3(10,20,30);

   print(rgb1);
   print(rgb2);
   print(rgb3);
   print(rgb3.r);
   print(rgb3.g);
   print(rgb3.b);

   std::cout << rgb1 << std::endl;
   std::cout << rgb2 << std::endl;
   std::cout << rgb3 << std::endl;
}
