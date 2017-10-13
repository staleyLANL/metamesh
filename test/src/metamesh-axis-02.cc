
#include "metamesh.h"

int main(void)
{
   metamesh::kip::axis<> axis;
   std::ofstream ofs("output/metamesh-axis-02.kip");

   const double a = 3;
   const double b = 2;
   const double c = 2;

   axis.origin.diameter *= a;

   axis.x.positive.line .diameter *= a;
   axis.x.positive.tick .length   *= b;
   axis.x.positive.tick .diameter *= c;
   axis.x.positive.arrow.diameter *= a;
   axis.x.negative.line .diameter *= a;
   axis.x.negative.tick .length   *= b;
   axis.x.negative.tick .diameter *= c;
   axis.x.negative.arrow.diameter *= a;

   axis.y.positive.line .diameter *= a;
   axis.y.positive.tick .length   *= b;
   axis.y.positive.tick .diameter *= c;
   axis.y.positive.arrow.diameter *= a;
   axis.y.negative.line .diameter *= a;
   axis.y.negative.tick .length   *= b;
   axis.y.negative.tick .diameter *= c;
   axis.y.negative.arrow.diameter *= a;

   axis.z.positive.line .diameter *= a;
   axis.z.positive.tick .length   *= b;
   axis.z.positive.tick .diameter *= c;
   axis.z.positive.arrow.diameter *= a;
   axis.z.negative.line .diameter *= a;
   axis.z.negative.tick .length   *= b;
   axis.z.negative.tick .diameter *= c;
   axis.z.negative.arrow.diameter *= a;

   for (int i = -10;  i <= 10;  i += 2)
   for (int j = -10;  j <= 10;  j += 2)
   for (int k = -10;  k <= 10;  k += 2) {
      axis.origin.x = i;
      axis.origin.y = j;
      axis.origin.z = k;
      ofs << axis;
   }
}
