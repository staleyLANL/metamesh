
#define METAMESH_ASSERT
#include "metamesh.h"
#include "metamesh-mesh.hh"
using metamesh::print;

int main(void)
{
   mesh0f3d m03(info(3.1415927,2.7182818));
   mesh1f3d m13(info(3.1415927,2.7182818));
   mesh2f3d m23(info(3.1415927,2.7182818));
   mesh3f3d m33(info(3.1415927,2.7182818));

   using metamesh::tup;

   // m03
   m03.push(node3d(1.2, 3.4, 5.6));
   m03.check();
   m03.check("here",0);
   print("m03");
   print(m03);
   print();

   // m13
   m13.push(node3d(0.0, 0.0, 0.0));
   m13.push(node3d(1.0, 0.0, 0.0));
   m13.push(node3d(1.0, 0.0, 1.0));
   m13.push(edge3d((tup,0,1)));
   m13.push(edge3d((tup,1,2)));
   m13.push(edge3d((tup,2,0)));
   m13.check();
   m13.check("here",0,0);
   print("m13");
   print(m13);
   print();

   // m23
   m23.push(node3d(0,0,0));  // origin
   m23.push(node3d(1,0,0));  // x == 1
   m23.push(node3d(0,1,0));  // y == 1
   m23.push(node3d(0,0,1));  // z == 1
   m23.push(edge3d((tup,0,1)));  // [0]: origin to x == 1
   m23.push(edge3d((tup,0,2)));  // [1]: origin to y == 1
   m23.push(edge3d((tup,0,3)));  // [2]: origin to z == 1
   m23.push(edge3d((tup,1,2)));  // [3]: x == 1 to y == 1
   m23.push(edge3d((tup,1,3)));  // [4]: x == 1 to z == 1
   m23.push(edge3d((tup,2,3)));  // [5]: y == 1 to z == 1
   m23.push(face3d((tup,0,3,1)));
   m23.push(face3d((tup,1,5,2)));
   m23.push(face3d((tup,0,4,2)));
   m23.push(face3d((tup,3,5,4)));
   m23.check();
   m23.check("here",0,0,0);
   print("m23");
   print(m23);
   print();

   // m33
   m33.push(node3d(0,0,0));  // origin
   m33.push(node3d(1,0,0));  // x == 1
   m33.push(node3d(0,1,0));  // y == 1
   m33.push(node3d(0,0,1));  // z == 1
   m33.push(edge3d((tup,0,1)));  // [0]: origin to x == 1
   m33.push(edge3d((tup,0,2)));  // [1]: origin to y == 1
   m33.push(edge3d((tup,0,3)));  // [2]: origin to z == 1
   m33.push(edge3d((tup,1,2)));  // [3]: x == 1 to y == 1
   m33.push(edge3d((tup,1,3)));  // [4]: x == 1 to z == 1
   m33.push(edge3d((tup,2,3)));  // [5]: y == 1 to z == 1
   m33.push(face3d((tup,0,3,1)));  // [0]
   m33.push(face3d((tup,1,5,2)));  // [1]
   m33.push(face3d((tup,0,4,2)));  // [2]
   m33.push(face3d((tup,3,5,4)));  // [3]
   m33.push(cell3d((tup,0,1,2,3)));  // tet
   m33.check();
   m33.check("here",0,0,0,0);
   print("m33");
   print(m33);

   // operator, (and thus operator() as well)
   print("\n(m13,edge[][])");
   print((m13,m13.edge[0][0]));  print((m13,m13.edge[0][1]));
   print((m13,m13.edge[1][0]));  print((m13,m13.edge[1][1]));
   print((m13,m13.edge[2][0]));  print((m13,m13.edge[2][1]));
   print("\n(m23,edge[][])");
   print((m23,m23.edge[0][0]));  print((m23,m23.edge[0][1]));
   print((m23,m23.edge[1][0]));  print((m23,m23.edge[1][1]));
   print((m23,m23.edge[2][0]));  print((m23,m23.edge[2][1]));
   print((m23,m23.edge[3][0]));  print((m23,m23.edge[3][1]));
   print((m23,m23.edge[4][0]));  print((m23,m23.edge[4][1]));
   print((m23,m23.edge[5][0]));  print((m23,m23.edge[5][1]));
   print("\n(m23,face[][])");
   print((m23,m23.face[0][0]));  print((m23,m23.face[0][1]));
   print((m23,m23.face[0][2]));  print((m23,m23.face[1][0]));
   print((m23,m23.face[1][1]));  print((m23,m23.face[1][2]));
   print((m23,m23.face[2][0]));  print((m23,m23.face[2][1]));
   print((m23,m23.face[2][2]));  print((m23,m23.face[3][0]));
   print((m23,m23.face[3][1]));  print((m23,m23.face[3][2]));
   print("\n(m33,edge[][])");
   print((m33,m33.edge[0][0]));  print((m33,m33.edge[0][1]));
   print((m33,m33.edge[1][0]));  print((m33,m33.edge[1][1]));
   print((m33,m33.edge[2][0]));  print((m33,m33.edge[2][1]));
   print((m33,m33.edge[3][0]));  print((m33,m33.edge[3][1]));
   print((m33,m33.edge[4][0]));  print((m33,m33.edge[4][1]));
   print((m33,m33.edge[5][0]));  print((m33,m33.edge[5][1]));
   print("\n(m33,face[][])");
   print((m33,m33.face[0][0]));  print((m33,m33.face[0][1]));
   print((m33,m33.face[0][2]));  print((m33,m33.face[1][0]));
   print((m33,m33.face[1][1]));  print((m33,m33.face[1][2]));
   print((m33,m33.face[2][0]));  print((m33,m33.face[2][1]));
   print((m33,m33.face[2][2]));  print((m33,m33.face[3][0]));
   print((m33,m33.face[3][1]));  print((m33,m33.face[3][2]));
   print("\n(m33,cell[][])");
   print((m33,m33.cell[0][0]));  print((m33,m33.cell[0][1]));
   print((m33,m33.cell[0][2]));  print((m33,m33.cell[0][3]));

   // const version of operator,
   const mesh0f3d &m03const = m03;  (void)m03const;
   const mesh1f3d &m13const = m13;
   const mesh2f3d &m23const = m23;
   const mesh3f3d &m33const = m33;

   print("\nconst begin");
   print( (m13const, m13const.edge[0][0]) );
   print( (m23const, m23const.edge[0][0]) );
   print( (m23const, m23const.face[0][0]) );
   print( (m33const, m33const.edge[0][0]) );
   print( (m33const, m33const.face[0][0]) );
   print( (m33const, m33const.cell[0][0]) );
   print("const end");

   // index_to
   print("\nindex begin");
   print( (m03const, metamesh::index_to<node3d,std::size_t>(0)) );
   print( (m13const, metamesh::index_to<edge3d,std::size_t>(0)) );
   print( (m23const, metamesh::index_to<face3d,std::size_t>(0)) );
   print( (m33const, metamesh::index_to<cell3d,std::size_t>(0)) );
   print("index end");

   // clear, then print again
   m03.clear();  print("\nm03");  print(m03);
   m13.clear();  print("\nm13");  print(m13);
   m23.clear();  print("\nm23");  print(m23);
   m33.clear();  print("\nm33");  print(m33);
}
