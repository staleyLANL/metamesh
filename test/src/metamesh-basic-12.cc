
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // setup
   const metamesh::loop n(10);
   n.reset();  // redundant here

   // begin, end, min, max
   print();
   print(n.begin());
   print(n.end());
   print(n.min());
   print(n.max());

   // conversion to std::size_t
   print();
   print(std::size_t(n));

   // ()
   print();
   print("()");
   while (n())
      std::cout << "   " << n;
   print();

   // fore, back
   print();
   print("fore, back");
   while (n.fore()) std::cout << "   " << n;
   print();
   while (n.back()) std::cout << "   " << n;
   print();

   // more, less
   print();
   print("more, less");
   while (n.more()) std::cout << "   " << n;
   print();
   while (n.less()) std::cout << "   " << n;
   print();

   // +
   print();
   print("+");
   print(n+100);
   print(100+n);

   // This would fail - intentionally - because metamesh::loop's
   // conversion to bool is made private. You should use () etc.
   // while (n)
   // {
   // }
}
