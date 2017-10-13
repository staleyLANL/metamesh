
#include "metamesh.h"

int main(void)
{
   // min
   metamesh::print(metamesh::min(3));
   metamesh::print(metamesh::min(3,2));
   metamesh::print(metamesh::min(3,2,5));
   metamesh::print(metamesh::min(3,2,5,11));
   metamesh::print(metamesh::min(3,2,5,11,7));

   // max
   metamesh::print(metamesh::max(3));
   metamesh::print(metamesh::max(3,2));
   metamesh::print(metamesh::max(3,2,5));
   metamesh::print(metamesh::max(3,2,5,11));
   metamesh::print(metamesh::max(3,2,5,11,7));
}
