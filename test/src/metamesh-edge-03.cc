
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using node = metamesh::node<metamesh::polar<2,double>>;
   using edge = metamesh::edge<metamesh::two<node>,flow<2>>;

   edge b((metamesh::tup,3,5));  // ctor(terms)
   edge c(flow<2>(1.23f,4.56f));  // ctor(base)
   b.fx = 3.1415927f;
   b.fy = 2.7182818f;
   c[0] = 10;
   c[1] = 20;
   print(b);
   print(c);
   print();

   b = c.terms();
   c = b.base();
   print(b);
   print(c);
   print();

   const edge d((metamesh::tup,1,2),flow<2>(3.4f,5.6f));
   b = d.terms();
   c = d.base ();
   print(b);
   print(c);
   print();

   d.check();
   d.check("context");
   d.check(3);
   d.check(3,"context");
}
