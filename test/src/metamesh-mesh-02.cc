
#define METAMESH_ASSERT
#include "metamesh.h"
#include "metamesh-mesh.hh"
using metamesh::print;

int main(void)
{
   // ------------------------
   // types
   // ------------------------

   // mesh0f0d
   print(sizeof(mesh0f0d::node_t));
   print(sizeof(mesh0f0d::zone_t));
   print(sizeof(mesh0f0d::base_t));
   print(sizeof(mesh0f0d::value_t));

   // mesh0f1d
   print(sizeof(mesh0f1d::node_t));
   print(sizeof(mesh0f1d::zone_t));
   print(sizeof(mesh0f1d::base_t));
   print(sizeof(mesh0f1d::value_t));

   // mesh0f2d
   print(sizeof(mesh0f2d::node_t));
   print(sizeof(mesh0f2d::zone_t));
   print(sizeof(mesh0f2d::base_t));
   print(sizeof(mesh0f2d::value_t));

   // mesh0f3d
   print(sizeof(mesh0f3d::node_t));
   print(sizeof(mesh0f3d::zone_t));
   print(sizeof(mesh0f3d::base_t));
   print(sizeof(mesh0f3d::value_t));

   // mesh1f1d
   print(sizeof(mesh1f1d::node_t));
   print(sizeof(mesh1f1d::edge_t));
   print(sizeof(mesh1f1d::zone_t));
   print(sizeof(mesh1f1d::base_t));
   print(sizeof(mesh1f1d::value_t));

   // mesh1f2d
   print(sizeof(mesh1f2d::node_t));
   print(sizeof(mesh1f2d::edge_t));
   print(sizeof(mesh1f2d::zone_t));
   print(sizeof(mesh1f2d::base_t));
   print(sizeof(mesh1f2d::value_t));

   // mesh1f3d
   print(sizeof(mesh1f3d::node_t));
   print(sizeof(mesh1f3d::edge_t));
   print(sizeof(mesh1f3d::zone_t));
   print(sizeof(mesh1f3d::base_t));
   print(sizeof(mesh1f3d::value_t));

   // mesh2f2d
   print(sizeof(mesh2f2d::node_t));
   print(sizeof(mesh2f2d::edge_t));
   print(sizeof(mesh2f2d::face_t));
   print(sizeof(mesh2f2d::zone_t));
   print(sizeof(mesh2f2d::base_t));
   print(sizeof(mesh2f2d::value_t));

   // mesh2f3d
   print(sizeof(mesh2f3d::node_t));
   print(sizeof(mesh2f3d::edge_t));
   print(sizeof(mesh2f3d::face_t));
   print(sizeof(mesh2f3d::zone_t));
   print(sizeof(mesh2f3d::base_t));
   print(sizeof(mesh2f3d::value_t));

   // mesh3f3d
   print(sizeof(mesh3f3d::node_t));
   print(sizeof(mesh3f3d::edge_t));
   print(sizeof(mesh3f3d::face_t));
   print(sizeof(mesh3f3d::cell_t));
   print(sizeof(mesh3f3d::zone_t));
   print(sizeof(mesh3f3d::base_t));
   print(sizeof(mesh3f3d::value_t));
}
