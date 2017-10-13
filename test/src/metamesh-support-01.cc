
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // ------------------------
   // tie, trim
   // ------------------------

   // tie
   print(metamesh::tie);
   print(metamesh::notie);
   print(metamesh::no_tie);
   assert(metamesh::notie == metamesh::no_tie);
   print();

   // trim
   print(metamesh::trim);
   print(metamesh::notrim);
   print(metamesh::no_trim);
   assert(metamesh::notrim == metamesh::no_trim);
   print();
}
