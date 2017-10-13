
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   // node, edge
   using node = metamesh::node<metamesh::polar<2,double>>;
   using edge = metamesh::edge<metamesh::two<node>,flow<2>>;

   // dimension
   print(node::dimension);
   print(edge::dimension);
   print();

   // types
   print(sizeof(edge::value_t));  // presumably double (underlying value)
   print(sizeof(edge::terms_t));  // two<node> (amounts to 2 std::size_t values)
   print(sizeof(edge::basis_t));  // node
   print(sizeof(edge::base_t));   // flow<2>
   print();

   // label
   print(edge::label());
   edge a;  // ctor()
   print(a.label());
   print();
}
