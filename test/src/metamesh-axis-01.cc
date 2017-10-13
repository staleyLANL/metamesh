
#include "metamesh.h"

int main(void)
{
   metamesh::kip::axis<> axis;

   /**/
   axis.scale = 1;
   axis.origin.x = 0;
   axis.origin.y = 0;
   axis.origin.z = 0;
   /**/

   axis.x.plane.on = true;
   axis.y.plane.on = true;
   axis.z.plane.on = true;
   axis.x.plane.color.first = metamesh::color::slight_red;
   axis.y.plane.color.first = metamesh::color::slight_green;
   axis.z.plane.color.first = metamesh::color::slight_blue;

   /*
   axis.x.negative.tick.on = false;
   axis.x.positive.arrow.on = false;
   axis.y.negative.on = false;
   axis.z.positive.on = false;
   */

   /*
   axis.x.plane.box.on = true;
   axis.y.plane.box.on = true;
   axis.z.plane.box.on = true;
   axis.x.plane.box.ysize = 0.1;
   axis.x.plane.box.zsize = 0.2;
   axis.y.plane.box.xsize = 0.3;
   axis.y.plane.box.zsize = 0.4;
   axis.z.plane.box.xsize = 0.5;
   axis.z.plane.box.ysize = 0.6;
   */

   /**/
   axis.x.plane.box.on = true;
   axis.y.plane.box.on = true;
   axis.z.plane.box.on = true;

   axis.x.plane.ellipsoid.on = true;
   axis.y.plane.ellipsoid.on = true;
   axis.z.plane.ellipsoid.on = true;

   axis.x.plane.box.ysize = 0.1;
   axis.x.plane.box.zsize = 0.2;
   axis.y.plane.box.xsize = 0.3;
   axis.y.plane.box.zsize = 0.4;
   axis.z.plane.box.xsize = 0.5;
   axis.z.plane.box.ysize = 0.6;

   axis.x.plane.ellipsoid.ysize = 0.15;
   axis.x.plane.ellipsoid.zsize = 0.25;
   axis.y.plane.ellipsoid.xsize = 0.35;
   axis.y.plane.ellipsoid.zsize = 0.45;
   axis.z.plane.ellipsoid.xsize = 0.55;
   axis.z.plane.ellipsoid.ysize = 0.65;
   /**/

   std::ofstream ofs("output/metamesh-axis-01.kip");
   ofs << axis;

   std::cout << axis << std::endl;
}
