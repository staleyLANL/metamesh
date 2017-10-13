
#include "metamesh.h"
using metamesh::print;
using namespace metamesh::color;

int main(void)
{
   // spectrum6
   const metamesh::loop s6(spectrum6.size());
   while (s6())
      print(spectrum6[s6]);

   // spectrum12
   const metamesh::loop s12(spectrum12.size());
   while (s12())
      print(spectrum12[s12]);
}
