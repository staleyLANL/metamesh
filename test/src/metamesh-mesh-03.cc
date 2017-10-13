
#define METAMESH_ASSERT
#include "metamesh.h"
#include "metamesh-mesh.hh"
using metamesh::print;

int main(void)
{
   // constructors, assignment
   mesh0f0d a;  mesh0f0d k(info(5.6,7.8));  a = info(1.2,3.4);
   mesh0f1d b;  mesh0f1d l(info(5.6,7.8));  b = info(1.2,3.4);
   mesh0f2d c;  mesh0f2d m(info(5.6,7.8));  c = info(1.2,3.4);
   mesh0f3d d;  mesh0f3d n(info(5.6,7.8));  d = info(1.2,3.4);
   mesh1f1d e;  mesh1f1d o(info(5.6,7.8));  e = info(1.2,3.4);
   mesh1f2d f;  mesh1f2d p(info(5.6,7.8));  f = info(1.2,3.4);
   mesh1f3d g;  mesh1f3d q(info(5.6,7.8));  g = info(1.2,3.4);
   mesh2f2d h;  mesh2f2d r(info(5.6,7.8));  h = info(1.2,3.4);
   mesh2f3d i;  mesh2f3d s(info(5.6,7.8));  i = info(1.2,3.4);
   mesh3f3d j;  mesh3f3d t(info(5.6,7.8));  j = info(1.2,3.4);

   // elements
   prs(a.node);  prs(a.zone);
   prs(b.node);  prs(b.zone);
   prs(c.node);  prs(c.zone);
   prs(d.node);  prs(d.zone);
   prs(e.node);  prs(e.edge);  prs(e.zone);
   prs(f.node);  prs(f.edge);  prs(f.zone);
   prs(g.node);  prs(g.edge);  prs(g.zone);
   prs(h.node);  prs(h.edge);  prs(h.face);  prs(h.zone);
   prs(i.node);  prs(i.edge);  prs(i.face);  prs(i.zone);
   prs(j.node);  prs(j.edge);  prs(j.face);  prs(j.cell);  prs(j.zone);

   const mesh3f3d u(info(1.234,5.678));
   print(j.base());
   print(t.base());
   print(u.base());
   print();
}
