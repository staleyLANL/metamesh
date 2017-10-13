
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

   const metamesh::loop a(0, true,  true );
   const metamesh::loop b(0, true,  false);
   const metamesh::loop c(0, false, true );
   const metamesh::loop d(0, false, false);

   const metamesh::loop e(1, true,  true );
   const metamesh::loop f(1, true,  false);
   const metamesh::loop g(1, false, true );
   const metamesh::loop h(1, false, false);

   const metamesh::loop i(2, true,  true );
   const metamesh::loop j(2, true,  false);
   const metamesh::loop k(2, false, true );
   const metamesh::loop l(2, false, false);

   const metamesh::loop m(5, true,  true );
   const metamesh::loop n(5, true,  false);
   const metamesh::loop o(5, false, true );
   const metamesh::loop p(5, false, false);

   const metamesh::loop q(v, true,  true );
   const metamesh::loop r(v, true,  false);
   const metamesh::loop s(v, false, true );
   const metamesh::loop t(v, false, false);

   print();
   prt("(0, true,  true ):");  while (a()) prt(a);  print();
   prt("(0, true,  false):");  while (b()) prt(b);  print();
   prt("(0, false, true ):");  while (c()) prt(c);  print();
   prt("(0, false, false):");  while (d()) prt(d);  print();
   print();
   prt("(1, true,  true ):");  while (e()) prt(e);  print();
   prt("(1, true,  false):");  while (f()) prt(f);  print();
   prt("(1, false, true ):");  while (g()) prt(g);  print();
   prt("(1, false, false):");  while (h()) prt(h);  print();
   print();
   prt("(2, true,  true ):");  while (i()) prt(i);  print();
   prt("(2, true,  false):");  while (j()) prt(j);  print();
   prt("(2, false, true ):");  while (k()) prt(k);  print();
   prt("(2, false, false):");  while (l()) prt(l);  print();
   print();
   prt("(5, true,  true ):");  while (m()) prt(m);  print();
   prt("(5, true,  false):");  while (n()) prt(n);  print();
   prt("(5, false, true ):");  while (o()) prt(o);  print();
   prt("(5, false, false):");  while (p()) prt(p);  print();
   print();
   prt("(v, true,  true ):");  while (q()) prt(q);  print();
   prt("(v, true,  false):");  while (r()) prt(r);  print();
   prt("(v, false, true ):");  while (s()) prt(s);  print();
   prt("(v, false, false):");  while (t()) prt(t);  print();
}
