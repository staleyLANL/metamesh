
#include "metamesh.h"
using metamesh::print;
#include "metamesh-node.hh"

int main(void)
{
   // ------------------------
   // cartesian<3,double>
   // ------------------------

   {
   // coordinate system, and node type
   using sys  = metamesh::cartesian<3,double>;
   using node = metamesh::node<sys,ijk<3>>;

   // terms, base
   const sys terms(1.2, 3.4, 5.6);
   ijk<3> base;
   base.i = 10;
   base.j = 20;
   base.k = 30;

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
   node e(9.87, 6.54, 3.21);
   const node f(9.87, 6.54, 3.21, base);

   // node: label from object
   print(a.label());

   // node: value, label from terms
   print(e.value(metamesh::component<0>()));
   print(e.value(metamesh::component<1>()));
   print(e.value(metamesh::component<2>()));
   print(f.value(metamesh::component<0>()));
   print(f.value(metamesh::component<1>()));
   print(f.value(metamesh::component<2>()));
   print(f.label(metamesh::component<0>()));
   print(f.label(metamesh::component<1>()));
   print(f.label(metamesh::component<2>()));

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
   a(11.1, 13.2, 17.3);
   print(a);

   print(f.check());

   // node: i/o
   std::ifstream ifs("input/metamesh-node-05.in");
   ifs >> a;
   std::cout << a << std::endl;

   // node: vector operator,
   std::vector<node> vec;
   vec.push_back(node(1.1, 2.1, 3.1, ijk<3>(1,2,3)));
   vec.push_back(node(1.2, 2.2, 3.2, ijk<3>(4,5,6)));
   vec.push_back(node(1.3, 2.3, 3.3, ijk<3>(7,8,9)));

   print((vec,0));
   print((vec,1));
   print((vec,2));

   // node: access to additional terms functionality
   print(a.dimension);
   print(a.x);
   print(a.y);
   print(a.z);
   print(metamesh::point<double>(a));
   }
}
