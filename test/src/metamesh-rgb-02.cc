
#include "kip.h"
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   kip::rgb k1(100,110,120);
   metamesh::rgb rgb1(k1);
   kip::rgb k2(rgb1);  // because metamesh::rgb has conversion to kip::rgb
   (void)k2;//qqq

   kip::crayola c = kip::crayola::brick_red;
   metamesh::rgb rgb2(c);

   // metamesh:: in spite of above "using" because kip:: has print() too
   //qqq metamesh::print(k1);
   print(rgb1);
   //qqq metamesh::print(k2);
   print(rgb2);

   // qqq Deal with these after changing operator<</operator>>
   // qqq scopes throughout kip
}
