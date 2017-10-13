
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   std::vector<double> vec;
   vec.push_back(1.0);
   vec.push_back(1.1);
   vec.push_back(1.2);
   vec.push_back(1.3);
   vec.push_back(1.4);

   const std::vector<double> constvec(vec.begin(), vec.end());

   // zero
   metamesh::zero<double,std::size_t> a;
   print(metamesh::zero<double>::has_const_size);
   print(a.has_const_size);
   print(a.size());
   metamesh::zero<double,std::size_t>::basis_t dub = 3.14159;
   print(dub);

   const metamesh::zero<double,std::size_t> b((metamesh::tup));
   metamesh::zero<double,std::size_t> c(b);
   metamesh::zero<double,int> d(b);
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

   /*
   // operator()
   print(a(vec,4));
   print(a(constvec,0));
   */
}
