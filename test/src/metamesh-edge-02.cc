
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using node = metamesh::node<metamesh::polar<2,double>>;
   using edge = metamesh::edge<metamesh::two<node>,flow<2>>;

   edge a((metamesh::tup,3,5),flow<2>(1.23f,4.56f));  // ctor(terms,base)
   print(a.has_const_size);  // true
   print(a.size());  // 2
   print(a[0]);  // 3
   print(a[1]);  // 5
   print(a);
   a.clear();
   a.prepare(2);
   print();

   std::ifstream ifs("input/metamesh-edge-02.in");
   ifs >> a;
   print(a);
   print();
}
