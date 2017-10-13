
#include "metamesh.h"
using metamesh::print;
#include "metamesh-node.hh"

int main(void)
{
   // ------------------------
   // cartesian<0,double>
   // ------------------------

   {
   // coordinate system, and node type
   using sys  = metamesh::cartesian<0,double>;
   using node = metamesh::node<sys,ijk<0>>;

   // terms, base
   const sys terms;
   ijk<0> base;

   // node: types, label from static
   print(sizeof(node::value_t));  // double
   print(sizeof(node::terms_t));  // cartesian
   print(sizeof(node::base_t));   // ijk
   print(node::label());

   // node: construction
   node a;
   node b(terms);
   node c(base);
   const node d(terms,base);

   // node: label from object
   print(a.label());

   // node: assignment to terms/base
   a = terms;
   a = base;

   // node: non-const and const terms() and base()
   // for terms(), might not have operator<<
   (void)a.terms();
   print(a.base());
   (void)d.terms();
   print(d.base());

   // node: operator() "assignment"
   print(a);
   print(a);

   print(d.check());

   // node: i/o
   std::ifstream ifs("input/metamesh-node-02.in");
   ifs >> a;
   std::cout << a << std::endl;

   // node: vector operator,
   std::vector<node> vec;
   vec.push_back(node(ijk<0>()));
   vec.push_back(node(ijk<0>()));
   vec.push_back(node(ijk<0>()));

   print((vec,0));
   print((vec,1));
   print((vec,2));

   // node: access to additional terms functionality
   print(a.dimension);
   print(metamesh::point<double>(a));
   }
}
