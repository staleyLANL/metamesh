
// qqq This file needs some filling-in

#define METAMESH_ASSERT
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // ------------------------
   // 0-form
   // ------------------------

   {
   }



   // ------------------------
   // 1-form
   // ------------------------

   {
   }



   // ------------------------
   // 2-form
   // face<node>
   // ------------------------

   {
   }



   // ------------------------
   // 2-form
   // face<edge>
   // ------------------------

   {
   }



   // ------------------------
   // 3-form
   // face<node>
   // cell<node>
   // ------------------------

   {
   }



   // ------------------------
   // 3-form
   // face<node>
   // cell<edge>
   // ------------------------

   {
   }



   // ------------------------
   // 3-form
   // face<node>
   // cell<face>
   // ------------------------

   {
   }



   // ------------------------
   // 3-form
   // face<edge>
   // cell<node>
   // ------------------------

   /*
   {
      using node = metamesh::node<metamesh::cartesian<3>>;
      using edge = metamesh::edge<metamesh::two   <node>>;
      using face = metamesh::face<metamesh::four  <edge>>;
      using cell = metamesh::cell<metamesh::eight <node>>;
      using mesh = metamesh::mesh<node, edge, face, cell>;
      mesh m;
      using metamesh::tup;

      // nodes
      m.push(node(0,0,0));
      m.push(node(1,0,0));
      m.push(node(1,1,0));
      m.push(node(0,1,0));
      m.push(node(0,0,1));
      m.push(node(1,0,1));
      m.push(node(1,1,1));
      m.push(node(0,1,1));

      // edges
      m.push(edge((tup,0,1)));
      m.push(edge((tup,1,2)));
      m.push(edge((tup,2,3)));
      m.push(edge((tup,3,0)));
      m.push(edge((tup,0,4)));
      m.push(edge((tup,1,5)));
      m.push(edge((tup,2,6)));
      m.push(edge((tup,3,7)));
      m.push(edge((tup,4,5)));
      m.push(edge((tup,5,6)));
      m.push(edge((tup,6,7)));
      m.push(edge((tup,7,0)));  // qqq should be 7,4

      // faces
      m.push(face((tup,0,1, 2, 3)));
      m.push(face((tup,0,5, 8, 4)));
      m.push(face((tup,1,6, 9, 5)));
      m.push(face((tup,2,7,10, 6)));
      m.push(face((tup,3,4,11, 7)));
      m.push(face((tup,8,9,10,11)));

      // cells
      m.push(cell((tup,0,1,2,3,4,5,6,7)));

      // print
      print(m.node[0]);  print((m.node,0));
      print(m.edge[0]);  print((m.edge,0));
      print(m.face[0]);  print((m.face,0));
      print(m.cell[0]);  print((m.cell,0));
      print();

      // loop
      const metamesh::loop c(m.cell);

      // cell
      while (c())
         print((m.cell,c));
      print();

      // cell node
      while (c()) { const metamesh::loop n((m.cell,c));
      while (n())
         print((m.cell,c)(m.node,n));
      }
      print();

      //print((m.node,0)(m.node,0));  // bad
      //print((m.node,0)(m.edge,0));  // bad
      //print((m.node,0)(m.face,0));  // bad
      //print((m.node,0)(m.cell,0));  // bad
      print((m.edge,0)(m.node,0));
      //print((m.edge,0)(m.edge,0));  // bad
      //print((m.edge,0)(m.face,0));  // bad
      //print((m.edge,0)(m.cell,0));  // bad
      //print((m.face,0)(m.node,0));  // bad
      print((m.face,0)(m.edge,0));
      //print((m.face,0)(m.face,0));  // bad
      //print((m.face,0)(m.cell,0));  // bad
      print((m.cell,0)(m.node,0));
      //print((m.cell,0)(m.edge,0));  // bad
      //print((m.cell,0)(m.face,0));  // bad
      //print((m.cell,0)(m.cell,0));  // bad
      print();
   }
   */



   // ------------------------
   // 3-form
   // face<edge>
   // cell<edge>
   // ------------------------

   /*
   {
      using node = metamesh::node<metamesh::cartesian<3>>;
      using edge = metamesh::edge<metamesh::two   <node>>;
      using face = metamesh::face<metamesh::four  <edge>>;
      using cell = metamesh::cell<metamesh::twelve<edge>>;
      using mesh = metamesh::mesh<node, edge, face, cell>;
      mesh m;
      using metamesh::tup;

      // nodes
      m.push(node(0,0,0));
      m.push(node(1,0,0));
      m.push(node(1,1,0));
      m.push(node(0,1,0));
      m.push(node(0,0,1));
      m.push(node(1,0,1));
      m.push(node(1,1,1));
      m.push(node(0,1,1));

      // edges
      m.push(edge((tup,0,1)));
      m.push(edge((tup,1,2)));
      m.push(edge((tup,2,3)));
      m.push(edge((tup,3,0)));
      m.push(edge((tup,0,4)));
      m.push(edge((tup,1,5)));
      m.push(edge((tup,2,6)));
      m.push(edge((tup,3,7)));
      m.push(edge((tup,4,5)));
      m.push(edge((tup,5,6)));
      m.push(edge((tup,6,7)));
      m.push(edge((tup,7,0)));  // qqq should be 7,4

      // faces
      m.push(face((tup,0,1, 2, 3)));
      m.push(face((tup,0,5, 8, 4)));
      m.push(face((tup,1,6, 9, 5)));
      m.push(face((tup,2,7,10, 6)));
      m.push(face((tup,3,4,11, 7)));
      m.push(face((tup,8,9,10,11)));

      // cells
      m.push(cell((tup,0,1,2,3,4,5,6,7,8,9,10,11)));

      // print
      print(m.node[0]);  print((m.node,0));
      print(m.edge[0]);  print((m.edge,0));
      print(m.face[0]);  print((m.face,0));
      print(m.cell[0]);  print((m.cell,0));
      print();

      // loop
      const metamesh::loop c(m.cell);

      // cell
      while (c())
         print((m.cell,c));
      print();

      // cell edge
      while (c()) { const metamesh::loop e((m.cell,c));
      while (e())
         print((m.cell,c)(m.edge,e));
      }
      print();

      // cell edge node
      while (c()) { const metamesh::loop e((m.cell,c));
      while (e()) { const metamesh::loop n((m.cell,c)(m.edge,e));
      while (n())
         print((m.cell,c)(m.edge,e)(m.node,n));
      }}
      print();

      //print((m.node,0)(m.node,0));  // bad
      //print((m.node,0)(m.edge,0));  // bad
      //print((m.node,0)(m.face,0));  // bad
      //print((m.node,0)(m.cell,0));  // bad
      print((m.edge,0)(m.node,0));
      //print((m.edge,0)(m.edge,0));  // bad
      //print((m.edge,0)(m.face,0));  // bad
      //print((m.edge,0)(m.cell,0));  // bad
      //print((m.face,0)(m.node,0));  // bad
      print((m.face,0)(m.edge,0));
      //print((m.face,0)(m.face,0));  // bad
      //print((m.face,0)(m.cell,0));  // bad
      //print((m.cell,0)(m.node,0));  // bad
      print((m.cell,0)(m.edge,0));
      //print((m.cell,0)(m.face,0));  // bad
      //print((m.cell,0)(m.cell,0));  // bad
      print();
   }
   */



   // ------------------------
   // 3-form
   // face<edge>
   // cell<face>
   // ------------------------

   {
      using node = metamesh::node<metamesh::cartesian<3>>;
      using edge = metamesh::edge<metamesh::two <node>>;
      using face = metamesh::face<metamesh::four<edge>>;
      using cell = metamesh::cell<metamesh::six <face>>;
      using mesh = metamesh::mesh<node, edge, face, cell>;
      mesh m;
      using metamesh::tup;

      // nodes
      m.push(node(0,0,0));
      m.push(node(1,0,0));
      m.push(node(1,1,0));
      m.push(node(0,1,0));
      m.push(node(0,0,1));
      m.push(node(1,0,1));
      m.push(node(1,1,1));
      m.push(node(0,1,1));

      // edges
      m.push(edge((tup,0,1)));
      m.push(edge((tup,1,2)));
      m.push(edge((tup,2,3)));
      m.push(edge((tup,3,0)));
      m.push(edge((tup,0,4)));
      m.push(edge((tup,1,5)));
      m.push(edge((tup,2,6)));
      m.push(edge((tup,3,7)));
      m.push(edge((tup,4,5)));
      m.push(edge((tup,5,6)));
      m.push(edge((tup,6,7)));
      m.push(edge((tup,7,0)));  // qqq should be 7,4

      // faces
      m.push(face((tup,0,1, 2, 3)));
      m.push(face((tup,0,5, 8, 4)));
      m.push(face((tup,1,6, 9, 5)));
      m.push(face((tup,2,7,10, 6)));
      m.push(face((tup,3,4,11, 7)));
      m.push(face((tup,8,9,10,11)));

      // cells
      m.push(cell((tup,0,1,2,3,4,5)));

      // print
      print(m.node[0]);  print((m.node,0));
      print(m.edge[0]);  print((m.edge,0));
      print(m.face[0]);  print((m.face,0));
      print(m.cell[0]);  print((m.cell,0));
      print();

      // loop
      const metamesh::loop c(m.cell);

      // cell
      while (c())
         print((m.cell,c));
      print();

      // cell face
      while (c()) { const metamesh::loop f((m.cell,c));
      while (f())
         print((m.cell,c)(m.face,f));
      }
      print();

      // cell face edge
      while (c()) { const metamesh::loop f((m.cell,c));
      while (f()) { const metamesh::loop e((m.cell,c)(m.face,f));
      while (e())
         print((m.cell,c)(m.face,f)(m.edge,e));
      }}
      print();

      // cell face edge node
      while (c()) { const metamesh::loop f((m.cell,c));
      while (f()) { const metamesh::loop e((m.cell,c)(m.face,f));
      while (e()) { const metamesh::loop n((m.cell,c)(m.face,f)(m.edge,e));
      while (n())
         print((m.cell,c)(m.face,f)(m.edge,e)(m.node,n));
      }}}
      print();

      // print((m.node,0)(m.node,0));  // bad
      // print((m.node,0)(m.edge,0));  // bad
      // print((m.node,0)(m.face,0));  // bad
      // print((m.node,0)(m.cell,0));  // bad
      print((m.edge,0)(m.node,0));
      // print((m.edge,0)(m.edge,0));  // bad
      // print((m.edge,0)(m.face,0));  // bad
      // print((m.edge,0)(m.cell,0));  // bad
      // print((m.face,0)(m.node,0));  // bad
      print((m.face,0)(m.edge,0));
      // print((m.face,0)(m.face,0));  // bad
      // print((m.face,0)(m.cell,0));  // bad
      // print((m.cell,0)(m.node,0));  // bad
      // print((m.cell,0)(m.edge,0));  // bad
      print((m.cell,0)(m.face,0));
      // print((m.cell,0)(m.cell,0));  // bad
      print();
   }
}
