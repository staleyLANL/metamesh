
#include "metamesh.h"
using metamesh::print;

// prt
template<class T>
inline void prt(const T &value)
{
   std::cout << "   " << value;
}

// main
int main(void)
{
   std::vector<int> v;
   v.push_back( 2);  v.push_back( 3);  v.push_back( 5);  v.push_back( 7);
   v.push_back(11);  v.push_back(13);  v.push_back(17);  v.push_back(19);

   const metamesh::loop a(0, 0, 0);
   const metamesh::loop b(0, 1, 2);
   const metamesh::loop c(0, 5, 3);
   const metamesh::loop d(0, 4, 5);

   const metamesh::loop e(1, 0, 0);
   const metamesh::loop f(1, 1, 2);
   const metamesh::loop g(1, 5, 3);
   const metamesh::loop h(1, 4, 5);

   const metamesh::loop i(2, 0, 0);
   const metamesh::loop j(2, 1, 2);
   const metamesh::loop k(2, 5, 3);
   const metamesh::loop l(2, 4, 5);

   const metamesh::loop m(5, 0, 0);
   const metamesh::loop n(5, 1, 2);
   const metamesh::loop o(5, 5, 3);
   const metamesh::loop p(5, 4, 5);

   const metamesh::loop q(v, 0, 0);
   const metamesh::loop r(v, 1, 2);
   const metamesh::loop s(v, 5, 3);
   const metamesh::loop t(v, 4, 5);

   print();
   prt("(0, 0, 0):");  while (a()) prt(a);  print();
   prt("(0, 1, 2):");  while (b()) prt(b);  print();
   prt("(0, 5, 3):");  while (c()) prt(c);  print();
   prt("(0, 4, 5):");  while (d()) prt(d);  print();
   print();
   prt("(1, 0, 0):");  while (e()) prt(e);  print();
   prt("(1, 1, 2):");  while (f()) prt(f);  print();
   prt("(1, 5, 3):");  while (g()) prt(g);  print();
   prt("(1, 4, 5):");  while (h()) prt(h);  print();
   print();
   prt("(2, 0, 0):");  while (i()) prt(i);  print();
   prt("(2, 1, 2):");  while (j()) prt(j);  print();
   prt("(2, 5, 3):");  while (k()) prt(k);  print();
   prt("(2, 4, 5):");  while (l()) prt(l);  print();
   print();
   prt("(5, 0, 0):");  while (m()) prt(m);  print();
   prt("(5, 1, 2):");  while (n()) prt(n);  print();
   prt("(5, 5, 3):");  while (o()) prt(o);  print();
   prt("(5, 4, 5):");  while (p()) prt(p);  print();
   print();
   prt("(v, 0, 0):");  while (q()) prt(q);  print();
   prt("(v, 1, 2):");  while (r()) prt(r);  print();
   prt("(v, 5, 3):");  while (s()) prt(s);  print();
   prt("(v, 4, 5):");  while (t()) prt(t);  print();
}
