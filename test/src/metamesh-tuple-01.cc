
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // tup
   print(metamesh::tup);

   // index_to
   metamesh::index_to<int,std::size_t> i1;
   metamesh::index_to<int,double> i2(1.23);  // wouldn't normally use double
   i1 = 100;
   double d = double(i2);

   print(i1);
   print(i2);
   print(d);

   std::ifstream ifs("input/metamesh-tuple-01.in");
   ifs >> i2;
   print(i2);
}
