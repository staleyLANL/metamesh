
#define METAMESH_ASSERT
#include "metamesh.h"

int main(void)
{
   // This should succeed
   metamesh_assert(true);

   // This would fail
   // metamesh_assert(false);
}
