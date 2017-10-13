
#define METAMESH_KWINDOW
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   metamesh::point<> a(1,2,3);
   metamesh::point<> b(4,5,6);
   metamesh::point<> c(b);

   print(a);
   print(b);
   print(c);
}
