
#include "metamesh.h"

int main(void)
{
   std::cout << sizeof(metamesh::default_real_t) << std::endl;
   std::cout << sizeof(metamesh::default_base_t) << std::endl;

   metamesh::diagnostic_t d = metamesh::diagnostic_good;
   std::cout << d << std::endl;

   std::cout << metamesh::diagnostic_error   << std::endl;
   std::cout << metamesh::diagnostic_warning << std::endl;
   std::cout << metamesh::diagnostic_note    << std::endl;
   std::cout << metamesh::diagnostic_good    << std::endl;
}
