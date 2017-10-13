
#define METAMESH_ASSERT
#include "metamesh.h"
#include "metamesh-mesh.hh"
using metamesh::print;

int main(void)
{
   mesh0f3d m03;  const mesh0f3d m03c;
   mesh1f3d m13;  const mesh1f3d m13c;
   mesh2f3d m23;  const mesh2f3d m23c;
   mesh3f3d m33;  const mesh3f3d m33c;

   using metamesh::component;

   print(m03.label(component<0>()));  print(m03c.label(component<0>()));
   print();

   print(m13.label(component<0>()));  print(m13c.label(component<0>()));
   print(m13.label(component<1>()));  print(m13c.label(component<1>()));
   print();

   print(m23.label(component<0>()));  print(m23c.label(component<0>()));
   print(m23.label(component<1>()));  print(m23c.label(component<1>()));
   print(m23.label(component<2>()));  print(m23c.label(component<2>()));
   print();

   print(m33.label(component<0>()));  print(m33c.label(component<0>()));
   print(m33.label(component<1>()));  print(m33c.label(component<1>()));
   print(m33.label(component<2>()));  print(m33c.label(component<2>()));
   print(m33.label(component<3>()));  print(m33c.label(component<3>()));
   print();
}
