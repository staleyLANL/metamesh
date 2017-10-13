
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   /*
   using schar = signed char;
   */
   using quad = metamesh::quad;

   /*
   // sqrt
   print(metamesh::sqrt(float (3)));
   print(metamesh::sqrt(double(3)));
   print(metamesh::sqrt(quad  (3)));

   // abs
   print(int(metamesh::abs(schar (-2))));
   print(metamesh::abs(short (-2)));
   print(metamesh::abs(int   (-2)));
   print(metamesh::abs(long  (-2)));
   print(metamesh::abs(float (-2)));
   print(metamesh::abs(double(-2)));
   print(metamesh::abs(quad  (-2)));
   // qqq how about generic one??? print(metamesh::abs());

   // pow
   print(metamesh::pow(float (3), int   (4)));
   print(metamesh::pow(float (3), float (4)));
   print(metamesh::pow(double(3), int   (4)));
   print(metamesh::pow(double(3), double(4)));
   print(metamesh::pow(quad  (3), int   (4)));
   print(metamesh::pow(quad  (3), quad  (4)));

   // sin
   print(metamesh::sin(float (metamesh::pi/4)));
   print(metamesh::sin(double(metamesh::pi/4)));
   print(metamesh::sin(quad  (metamesh::pi/4)));

   // cos
   print(metamesh::cos(float (metamesh::pi/4)));
   print(metamesh::cos(double(metamesh::pi/4)));
   print(metamesh::cos(quad  (metamesh::pi/4)));
   */

   // round
   print(metamesh::internal::rnd<int>(float (+3.1)));
   print(metamesh::internal::rnd<int>(float (-3.1)));
   print(metamesh::internal::rnd<int>(float (+3.9)));
   print(metamesh::internal::rnd<int>(float (-3.9)));
   print(metamesh::internal::rnd<int>(double(+3.1)));
   print(metamesh::internal::rnd<int>(double(-3.1)));
   print(metamesh::internal::rnd<int>(double(+3.9)));
   print(metamesh::internal::rnd<int>(double(-3.9)));
   print(metamesh::internal::rnd<int>(quad  (+3.1)));
   print(metamesh::internal::rnd<int>(quad  (-3.1)));
   print(metamesh::internal::rnd<int>(quad  (+3.9)));
   print(metamesh::internal::rnd<int>(quad  (-3.9)));

   // twice
   print(metamesh::op::twice(10));
   print(metamesh::op::twice(10.2));

   // square
   print(metamesh::op::square(10));
   print(metamesh::op::square(10.2));
}
