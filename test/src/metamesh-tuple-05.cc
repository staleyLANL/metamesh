
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

   // tuple<5>
   metamesh::tuple<5,double,std::size_t> a;
   print(metamesh::tuple<5,double>::has_const_size);
   print(a.has_const_size);
   print(a.size());
   metamesh::tuple<5,double,std::size_t>::basis_t dub = 3.14159;
   print(dub);

   const metamesh::tuple<5,double,std::size_t> b((metamesh::tup,4,0,3,1,2));
   metamesh::tuple<5,double,std::size_t> c(b);
   metamesh::tuple<5,double,int> d(b);
   print();

   print(b);
   print(c);
   print(d);
   print();

   print(b[0]);  print(b[1]);  print(b[2]);  print(b[3]);  print(b[4]);
   print(c[0]);  print(c[1]);  print(c[2]);  print(c[3]);  print(c[4]);
   print();

   // prepare, push
   d.prepare(5);
   d.push(1000,0);
   d.push(2000,1);
   d.push(3000,2);
   d.push(4000,3);
   d.push(5000,4);
   print(d);
   print();

   /*
   // like "face", "node" 0,1,2,3,4 (maps to nodes 4,0,3,1,2; see above)
   print("qqq...");
   print(b(vec,0));
   print(b(vec,1));
   print(b(vec,2));
   print(b(vec,3));
   print(b(vec,4));
   print(b(constvec,0));
   print(b(constvec,1));
   print(b(constvec,2));
   print(b(constvec,3));
   print(b(constvec,4));
   */

   // find
   print(metamesh::find(b,10));
   print(metamesh::find(b,4));
   print();
}
