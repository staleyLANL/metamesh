
#include "metamesh.h"

int main(void)
{
   // stub
   metamesh::stub s;

   // both of these should print diagnostic_good
   std::cout << s.check() << std::endl;
   std::cout << s.check("unused argument") << std::endl;

   // both of these are in fact no-ops
   std::cin  >> s;
   std::cout << s;
}
