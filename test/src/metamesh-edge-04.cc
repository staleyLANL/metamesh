
#include "metamesh.h"
#include "metamesh-node.hh"
#include "metamesh-edge.hh"
using metamesh::print;

int main(void)
{
   using node = metamesh::node<metamesh::polar<2,double>>;
   using edge = metamesh::edge<metamesh::two<node>,flow<2>>;

   std::vector<edge> edges;
   edges.push_back(edge((metamesh::tup,1,2),flow<2>(1.2f,2.3f)));
   edges.push_back(edge((metamesh::tup,3,4),flow<2>(3.4f,4.5f)));
   edges.push_back(edge((metamesh::tup,5,6),flow<2>(5.6f,6.7f)));
   edges.push_back(edge((metamesh::tup,7,8),flow<2>(7.8f,8.9f)));
   edges.push_back(edge((metamesh::tup,9,0),flow<2>(9.0f,0.1f)));
   const std::vector<edge> &edges2 = edges;

   print((edges, 0));
   print((edges2,1));
   print((edges, 2));
   print((edges2,3));
   print((edges, 4));
   print();
}
