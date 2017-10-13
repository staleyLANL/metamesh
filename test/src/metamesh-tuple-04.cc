
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // tuple<2>
   metamesh::tuple<2,double,std::size_t> a;
   print(metamesh::tuple<2,double>::has_const_size);
   print(a.has_const_size);
   print(a.size());
   metamesh::tuple<2,double,std::size_t>::basis_t dub = 3.14159;
   print(dub);

   const metamesh::tuple<2,double,std::size_t> b((metamesh::tup,10,20));
   metamesh::tuple<2,double,std::size_t> c(b);
   metamesh::tuple<2,double,int> d(b);
   print();

   print(b);
   print(c);
   print(d);
   print();

   print(b[0]);  print(b[1]);
   print(c[0]);  print(c[1]);
   print();

   // prepare, push
   d.prepare(2);
   d.push(1000,0);
   d.push(2000,1);
   print(d);
   print();
}
