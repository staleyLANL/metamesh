
#define METAMESH_ASSERT
#include "metamesh.h"

int main(void)
{
   // ------------------------
   // types
   // ------------------------

   using node = metamesh::node<metamesh::cartesian<3>>;
   using edge = metamesh::edge<metamesh::two <node>>;
   using face = metamesh::face<metamesh::four<edge>>;
   using cell = metamesh::cell<metamesh::six <face>>;

   metamesh::mesh<node, edge, face, cell> mesh;
   using metamesh::tup;


   // ------------------------
   // initialize
   // ------------------------

   // nodes
   mesh.push(node(-1,-1,-1));
   mesh.push(node( 1,-1,-1));
   mesh.push(node( 1, 1,-1));
   mesh.push(node(-1, 1,-1));
   mesh.push(node(-1,-1, 1));
   mesh.push(node( 1,-1, 1));
   mesh.push(node( 1, 1, 1));
   mesh.push(node(-1, 1, 1));

   // edges
   mesh.push(edge((tup,0,1)));
   mesh.push(edge((tup,1,2)));
   mesh.push(edge((tup,2,3)));
   mesh.push(edge((tup,3,0)));
   mesh.push(edge((tup,0,4)));
   mesh.push(edge((tup,1,5)));
   mesh.push(edge((tup,2,6)));
   mesh.push(edge((tup,3,7)));
   mesh.push(edge((tup,4,5)));
   mesh.push(edge((tup,5,6)));
   mesh.push(edge((tup,6,7)));
   mesh.push(edge((tup,7,4)));

   // faces
   mesh.push(face((tup,0,1, 2, 3)));
   mesh.push(face((tup,0,5, 8, 4)));
   mesh.push(face((tup,1,6, 9, 5)));
   mesh.push(face((tup,2,7,10, 6)));
   mesh.push(face((tup,3,4,11, 7)));
   mesh.push(face((tup,8,9,10,11)));

   // cells
   mesh.push(cell((tup,0,1,2,3,4,5)));


   // ------------------------
   // write
   // ------------------------

   /*
   // simple version of later code
   std::ofstream ofs("output/metamesh-write-01.kip");
   metamesh::kip::ostream<> kout(ofs);
   metamesh::kip::axis<> axis;
   kout << axis;
   kout << mesh;
   */

   // file
   std::ofstream ofs("output/metamesh-write-01.kip");
   metamesh::kip::ostream<> kout(ofs);
   kout.scale = 1;
   kout.edge.begin = 0;
   kout.edge.end = kout.node.diameter/2 + kout.edge.link.arrow.length;
   //kout.edge.diameter   = 0.02;
   //kout.face.link.begin = 0.2;
   //kout.face.link.end   = 0.2;
   //kout.cell.link.begin = 0.4;
   //kout.cell.link.end   = 0.4;
   kout.face.link.on = true;
   kout.edge.link.floor.on = false;
   kout.edge.link.arrow.on = true;
   kout.cell.link.on = true;

   // color scheme
   //kout.default_colors();
   kout.silver_swirls();
   //kout.gem_tones();
   //kout.pearl_brite();
   //kout.metallic_fx();
   //kout.edge.link.floor.color = metamesh::color::white;
   //kout.edge.link.arrow.color = metamesh::color::black;

   // write axis
   metamesh::kip::axis<> axis;
   axis.scale = 2;
   axis.x.positive.tick.n = 0;
   axis.x.negative.tick.n = 1;
   axis.y.positive.tick.n = 2;
   axis.y.negative.tick.n = 3;
   axis.z.positive.tick.n = 4;
   axis.z.negative.tick.n = 5;
   kout << axis;

   // write mesh
   kout << mesh;
}
