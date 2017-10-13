
#include "metamesh.h"
using metamesh::print;
#include "metamesh-node.hh"

int main(void)
{
   // ------------------------
   // cartesian<2,double>
   // ------------------------

   {
   // coordinate system, and node type
   using sys  = metamesh::cartesian<2,double>;
   using node = metamesh::node<sys,ijk<2>>;

   // terms, base
   const sys terms(1.2, 3.4);
   ijk<2> base;
   base.i = 10;
   base.j = 20;

   // node: types, label from static
   print(sizeof(node::value_t));  // double
   print(sizeof(node::terms_t));  // cartesian
   print(sizeof(node::base_t));   // ijk
   print(node::label());

   // node: construction
   node a;
   node b(terms);
   node c(base);
   node d(terms,base);
   node e(9.87, 6.54);
   const node f(9.87, 6.54, base);

   // node: label from object
   print(a.label());

   // node: value, label from terms
   print(e.value(metamesh::component<0>()));
   print(e.value(metamesh::component<1>()));
   print(f.value(metamesh::component<0>()));
   print(f.value(metamesh::component<1>()));
   print(f.label(metamesh::component<0>()));
   print(f.label(metamesh::component<1>()));

   // node: assignment to terms/base
   a = terms;
   a = base;

   // node: non-const and const terms() and base()
   // for terms(), might not have operator<<
   (void)a.terms();
   print(a.base());
   (void)f.terms();
   print(f.base());

   // node: operator() "assignment"
   print(a);
   a(11.1, 13.2);
   print(a);

   print(f.check());

   // node: i/o
   std::ifstream ifs("input/metamesh-node-04.in");
   ifs >> a;
   std::cout << a << std::endl;

   // node: vector operator,
   std::vector<node> vec;
   vec.push_back(node(1.1, 2.1, ijk<2>(1,2)));
   vec.push_back(node(1.2, 2.2, ijk<2>(4,5)));
   vec.push_back(node(1.3, 2.3, ijk<2>(7,8)));

   print((vec,0));
   print((vec,1));
   print((vec,2));

   // node: access to additional terms functionality
   print(a.dimension);
   print(a.x);
   print(a.y);
   print(metamesh::point<double>(a));
   }
}
