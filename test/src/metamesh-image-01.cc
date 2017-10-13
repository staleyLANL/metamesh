
#include "kip.h"
#include "metamesh.h"

int main(void)
{
   // types
   using node = metamesh::node<metamesh::cartesian<3>>;
   using edge = metamesh::edge<metamesh::two <node>>;
   using face = metamesh::face<metamesh::four<edge>>;
   using cell = metamesh::cell<metamesh::six <face>>;
   metamesh::mesh<node, edge, face, cell> mesh;
   using metamesh::tup;

   // elements
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

   // scene
   kip::scene<> scene;
   scene.push(kip::sphere<>(0,0,0, 1, ::kip::rgb(100,200,0)));
   scene.resize(200,100);
   scene.trace();

   // image files
   metamesh::image a("output/a"              );  a.flip = true;
   metamesh::image b("output/b",       ""    );  b.flip = false;
   metamesh::image c("output/c",       "."   );  c.flip = true;
   metamesh::image d("output/d",       ".rgb");  d.flip = false;
   metamesh::image e("output/e",       "rgb" );  e.flip = true;
   metamesh::image f("output/f", 0           );  f.flip = false;
   metamesh::image g("output/g", 1,    ""    );  g.flip = true;
   metamesh::image h("output/h", 10,   "."   );  h.flip = false;
   metamesh::image i("output/i", 100,  ".rgb");  i.flip = true;
   metamesh::image j("output/j", 1000, "rgb" );  j.flip = false;

   // write
   a << scene;
   b << scene;
   c << scene;
   d << scene;
   e << scene;
   f << scene;  f << scene;  f << scene;  f << scene;
   g << scene;  g << scene;  g << scene;  g << scene;
   h << scene;  h << scene;  h << scene;  h << scene;
   i << scene;  i << scene;  i << scene;  i << scene;
   j << scene;  j << scene;  j << scene;  j << scene;
}
