
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

   prs(m03.elements(component<0>()));  prs(m03c.elements(component<0>()));
   prs(m13.elements(component<0>()));  prs(m13c.elements(component<0>()));
   prs(m13.elements(component<1>()));  prs(m13c.elements(component<1>()));
   prs(m23.elements(component<0>()));  prs(m23c.elements(component<0>()));
   prs(m23.elements(component<1>()));  prs(m23c.elements(component<1>()));
   prs(m23.elements(component<2>()));  prs(m23c.elements(component<2>()));
   prs(m33.elements(component<0>()));  prs(m33c.elements(component<0>()));
   prs(m33.elements(component<1>()));  prs(m33c.elements(component<1>()));
   prs(m33.elements(component<2>()));  prs(m33c.elements(component<2>()));
   prs(m33.elements(component<3>()));  prs(m33c.elements(component<3>()));
   print();
}
