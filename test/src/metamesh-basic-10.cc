
#include "metamesh.h"

int main(void)
{
   // note(), warning(), and error() print to metamesh::cerr, which by default
   // is std::cerr. In addition, they return values of the "diagnostic_t" enum
   // type, which we'll print with print() in each case...

   // note
   metamesh::print(
      metamesh::note(
         "This is an example note",
         "It happened in context A"
      )
   );

   // warning
   metamesh::print(
      metamesh::warning(
         "This is an example warning",
         "It happened in context B"
      )
   );

   // error
   metamesh::print(
      metamesh::error(
         "This is an example error",
         "It happened in context C"
      )
   );

   // addendum. This function doesn't return a value, so there's no print()
   metamesh::addendum(
      "This is an example addendum, probably to a note, warning, or error"
   );
}
