
// qqq Should put print()s in this file

#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // zero..twelve
   {
      metamesh::zero  <double,std::size_t> a;
      metamesh::one   <double,std::size_t> b(12);
      metamesh::two   <double,std::size_t> c(12,11);
      metamesh::three <double,std::size_t> d(12,11,10);
      metamesh::four  <double,std::size_t> e(12,11,10,9);
      metamesh::five  <double,std::size_t> f(12,11,10,9,8);
      metamesh::six   <double,std::size_t> g(12,11,10,9,8,7);
      metamesh::seven <double,std::size_t> h(12,11,10,9,8,7,6);
      metamesh::eight <double,std::size_t> i(12,11,10,9,8,7,6,5);
      metamesh::nine  <double,std::size_t> j(12,11,10,9,8,7,6,5,4);
      metamesh::ten   <double,std::size_t> k(12,11,10,9,8,7,6,5,4,3);
      metamesh::eleven<double,std::size_t> l(12,11,10,9,8,7,6,5,4,3,2);
      metamesh::twelve<double,std::size_t> m(12,11,10,9,8,7,6,5,4,3,2,1);
      print(b);  print(c);  print(d);  print(e);
      print(f);  print(g);  print(h);  print(i);
      print(j);  print(k);  print(l);  print(m);
   } {
      using metamesh::tup;
      metamesh::zero  <double,std::size_t> a((tup));
      metamesh::one   <double,std::size_t> b((tup,12));
      metamesh::two   <double,std::size_t> c((tup,12,11));
      metamesh::three <double,std::size_t> d((tup,12,11,10));
      metamesh::four  <double,std::size_t> e((tup,12,11,10,9));
      metamesh::five  <double,std::size_t> f((tup,12,11,10,9,8));
      metamesh::six   <double,std::size_t> g((tup,12,11,10,9,8,7));
      metamesh::seven <double,std::size_t> h((tup,12,11,10,9,8,7,6));
      metamesh::eight <double,std::size_t> i((tup,12,11,10,9,8,7,6,5));
      metamesh::nine  <double,std::size_t> j((tup,12,11,10,9,8,7,6,5,4));
      metamesh::ten   <double,std::size_t> k((tup,12,11,10,9,8,7,6,5,4,3));
      metamesh::eleven<double,std::size_t> l((tup,12,11,10,9,8,7,6,5,4,3,2));
      metamesh::twelve<double,std::size_t> m((tup,12,11,10,9,8,7,6,5,4,3,2,1));
      print(b);  print(c);  print(d);  print(e);
      print(f);  print(g);  print(h);  print(i);
      print(j);  print(k);  print(l);  print(m);
   }
}
