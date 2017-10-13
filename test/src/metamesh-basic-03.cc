
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   using quad = metamesh::quad;

   // some sizes
   print(sizeof(float));
   print(sizeof(double));
   print(sizeof(quad));

   // quad (long double)
   metamesh::quad q = sqrt(metamesh::quad(2));
   print(q);

   // version
   print(metamesh::version);

   // stub
   metamesh::stub s;
}
