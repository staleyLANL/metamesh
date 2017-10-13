
#define METAMESH_ASSERT
#include "metamesh.h"
#include "metamesh-mesh.hh"
using metamesh::print;

int main(void)
{
   // ------------------------
   // form, dimension, label
   // ------------------------

   // form
   print(mesh0f0d::form);
   print(mesh0f1d::form);
   print(mesh0f2d::form);
   print(mesh0f3d::form);
   print(mesh1f1d::form);
   print(mesh1f2d::form);
   print(mesh1f3d::form);
   print(mesh2f2d::form);
   print(mesh2f3d::form);
   print(mesh3f3d::form);
   print();

   // dimension
   print(mesh0f0d::dimension);
   print(mesh0f1d::dimension);
   print(mesh0f2d::dimension);
   print(mesh0f3d::dimension);
   print(mesh1f1d::dimension);
   print(mesh1f2d::dimension);
   print(mesh1f3d::dimension);
   print(mesh2f2d::dimension);
   print(mesh2f3d::dimension);
   print(mesh3f3d::dimension);
   print();

   // label
   print(mesh0f0d::label());
   print(mesh0f1d::label());
   print(mesh0f2d::label());
   print(mesh0f3d::label());
   print(mesh1f1d::label());
   print(mesh1f2d::label());
   print(mesh1f3d::label());
   print(mesh2f2d::label());
   print(mesh2f3d::label());
   print(mesh3f3d::label());
   print();
}
