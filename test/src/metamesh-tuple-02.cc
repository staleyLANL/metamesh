
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // tuple<0>
   metamesh::tuple<0,double,std::size_t> a;
   print(metamesh::tuple<0,double>::has_const_size);
   print(a.has_const_size);
   print(a.size());
   metamesh::tuple<0,double,std::size_t>::basis_t dub = 3.14159;
   print(dub);

   const metamesh::tuple<0,double,std::size_t> b((metamesh::tup));
   metamesh::tuple<0,double,std::size_t> c(b);
   metamesh::tuple<0,double,int> d(b);
   print();

   print(b);
   print(c);
   print(d);
   print();

   print(b[0]);
   print(c[0]);
   print();

   // prepare, push
   d.prepare(0);
   d.push(1000,0);
   print(d);
   print();
}
