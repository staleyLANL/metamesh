
#include "kip.h"
#include "metamesh.h"

int main(void)
{
   // types
   using node = metamesh::node<metamesh::cartesian<3>>;
   using edge = metamesh::edge<metamesh::two <node>>;
   using face = metamesh::face<metamesh::four<edge>>;
   using cell = metamesh::cell<metamesh::six <face>>;

   // mesh
   metamesh::mesh<node, edge, face, cell> mesh;

   // mesh elements
   using metamesh::tup;
   mesh.push(node(-1,-1,-1));  mesh.push(node( 1,-1,-1));
   mesh.push(node( 1, 1,-1));  mesh.push(node(-1, 1,-1));
   mesh.push(node(-1,-1, 1));  mesh.push(node( 1,-1, 1));
   mesh.push(node( 1, 1, 1));  mesh.push(node(-1, 1, 1));
   mesh.push(edge((tup,0,1)));  mesh.push(edge((tup,1,2)));
   mesh.push(edge((tup,2,3)));  mesh.push(edge((tup,3,0)));
   mesh.push(edge((tup,0,4)));  mesh.push(edge((tup,1,5)));
   mesh.push(edge((tup,2,6)));  mesh.push(edge((tup,3,7)));
   mesh.push(edge((tup,4,5)));  mesh.push(edge((tup,5,6)));
   mesh.push(edge((tup,6,7)));  mesh.push(edge((tup,7,4)));
   mesh.push(face((tup,0,1, 2, 3)));  mesh.push(face((tup,0,5, 8, 4)));
   mesh.push(face((tup,1,6, 9, 5)));  mesh.push(face((tup,2,7,10, 6)));
   mesh.push(face((tup,3,4,11, 7)));  mesh.push(face((tup,8,9,10,11)));
   mesh.push(cell((tup,0,1,2,3,4,5)));

   // axis, scene, file
   metamesh::kip::axis<> axis;
   metamesh::kip::scene<> scene;
   metamesh::image file("output/test", 1000, "rgb");

   // scene parameters
   scene.d = 8;
   scene.fov = 26;
   scene.resize(1000,1000);
   scene.anti = 5;

   const std::size_t nframe = 10;
   const metamesh::loop n(nframe);
   while (n()) {
      scene.theta = double(n)*nframe/double(nframe);

      scene << axis;
      scene.append = true; // qqq do something about this
      scene << mesh;

      std::cout << "file << scene" << std::endl;
      scene.light()[0](scene.target, scene.d, scene.theta+60, scene.phi+10);
      scene.render();
      file << scene;
   }
}
