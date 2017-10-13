
#define METAMESH_ASSERT
#include "metamesh.h"
#include "metamesh-mesh.hh"
using metamesh::print;

int main(void)
{
   std::ifstream ifs("input/metamesh-mesh-07.in");

   mesh0f3d m03;  ifs >> m03;
   mesh1f3d m13;  ifs >> m13;
   mesh2f3d m23;  ifs >> m23;
   mesh3f3d m33;  ifs >> m33;

   print("\nm03");  print(m03);
   print("\nm13");  print(m13);
   print("\nm23");  print(m23);
   print("\nm33");  print(m33);
}
