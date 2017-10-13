
#include <complex>
#include "kip.h"
#include "metamesh.h"

// number of nodes, number of frames, antialiasing
const std::size_t nu = 100;  // r
const std::size_t nv = 200;  // theta
const std::size_t nframes = 100;
const std::size_t anti = 1;

// types
using node2 = metamesh::node<metamesh::polar<2>>;
using edge2 = metamesh::edge<metamesh::two  <node2>>;
using face2 = metamesh::face<metamesh::four <node2>>;
using mesh2 = metamesh::mesh<node2,edge2,face2>;

using node3 = metamesh::node<metamesh::cartesian<3>>;
using edge3 = metamesh::edge<metamesh::two  <node3>>;
using face3 = metamesh::face<metamesh::four <node3>>;
using mesh3 = metamesh::mesh<node3,edge3,face3>;

// meshes
mesh2 imesh;
mesh3 omesh, middle;

// counter
std::size_t counter = 0;



// =============================================================================
// Override for node3
// =============================================================================

namespace metamesh {
namespace kip {

template<class OSTREAM>
struct write_node<OSTREAM,mesh3,node3> {
   OSTREAM &operator()(OSTREAM &s, const mesh3 &mesh, const node3 &onode)
   {
      // types
      using real = typename OSTREAM::real_t;
      using base = typename OSTREAM::base_t;

      // n, i, j
      const std::size_t n = std::size_t(&onode - &mesh.node[0]);
      const std::size_t i = n % nu;
      const std::size_t j = n / nu;

      // diameter, color
      if (i == 0 || j == 0 || i == nu-1 || j == nv-1) {
         s.node.diameter = double(internal::default_node_diameter*1.8);
         s.node.color = rgb(0,0,0);
      } else {
         s.node.diameter = double(internal::default_node_diameter*1.4);

         const double usigma=double(nu)/2, du=(double(i)-usigma)/(1.5*usigma);
         const double vsigma=double(nv)/2, dv=(double(j)-vsigma)/(2.0*vsigma);
         const double exp = 255*std::exp(-(du*du + dv*dv));

         using uchar = unsigned char;
         const uchar r = uchar(256*i/nu);
         const uchar g = uchar(256*j/nv), b = uchar(exp);
         s.node.color = rgb(r,g,b);
      }

      // corresponding input-mesh node
      const node2 inode = imesh.node[n];

      // center
      const point<real> c(onode);

      // angle
      const point<real> p(inode);  // from input node
      const real ax = 0.05*double(::counter) + double(pi)*p.x;
      const real ay = 0.02*double(::counter) + double(pi)*p.y;
      const real az = 0.08*double(::counter);
      const point<real> a(ax,ay,az);

      // radii
      const point<real> r(
         op::half(std::abs(s.scale * s.node.diameter * 0.3)),
         op::half(std::abs(s.scale * s.node.diameter * 1.0)),
         op::half(std::abs(s.scale * s.node.diameter * 1.5))
      );

      // node
      if (kip_no_or(!s.push(::kip::ellipsoid<real,base>(c,a,r,s.node.color))))
         s.stream
            << "box("
            <<  c << ", " << double(rad2deg)*a << ", "
            <<  r << ", " << s.node.color << ")\n";

      // done
      return s;
   }
};

}
}



// =============================================================================
// edge_and_face
// =============================================================================

template<class MESH>
void edge_and_face(const std::size_t nu, const std::size_t nv, MESH &mesh)
{
   using edge = typename MESH::edge_t;
   using face = typename MESH::face_t;

   // x-direction edges
   const metamesh::loop ix(nu,true,false);
   const metamesh::loop jx(nv);
   while (ix())
   while (jx()) {
      if ((std::size_t(jx) % 4) == 0) {
         const std::size_t n = nu*jx+ix;
         mesh.push(edge((metamesh::tup, n, n+1)));
      }
   }

   // y-direction edges
   const metamesh::loop iy(nu);
   const metamesh::loop jy(nv,true,false);
   while (iy())
   while (jy()) {
      if ((std::size_t(iy) % 4) == 0) {
         const std::size_t n = nu*jy+iy;
         mesh.push(edge((metamesh::tup, n, n+nu)));
      }
   }

   // faces
   while (ix())
   while (jy()) {
      const std::size_t n = nu*jy+ix;
      mesh.push(face((metamesh::tup, n, n+1, n+1+nu, n+nu)));
   }
}



// =============================================================================
// main
// =============================================================================

int main(void)
{
   // ------------------------
   // mesh: input
   // ------------------------

   const double pi = double(metamesh::pi);
   const double umin = 0.0, umax = 1.0;
   const double vmin = 0.0, vmax = 2*pi;

   // nodes
   const metamesh::loop j(nv);
   const metamesh::loop i(nu);
   while (j())
   while (i())
      imesh.push(node2(
         umin + double(i)*(umax-umin)/double(nu-1),
         vmin + double(j)*(vmax-vmin)/double(nv-1)
      ));

   // edges, faces
   edge_and_face(nu, nv, imesh);


   // ------------------------
   // mesh: output
   // ------------------------

   // nodes
   std::size_t n = 0;
   while (j())
   while (i()) {
      const metamesh::point<double> p(imesh.node[n]);
      const std::complex<double> w(p.x,p.y);

      const double g1 = -1.5 * (  // *
         w*(1.0-std::pow(w,4))/(std::pow(w,6)+std::sqrt(5)*w*w*w-1.0)).imag();
      const double g2 = -1.5 * (  // *
         w*(1.0+std::pow(w,4))/(std::pow(w,6)+std::sqrt(5)*w*w*w-1.0)).real();
      const double g3 = -0.5 + (  // +
           (1.0+std::pow(w,6))/(std::pow(w,6)+std::sqrt(5)*w*w*w-1.0)).imag();
      const double fac = 1/(g1*g1 + g2*g2 + g3*g3);

      const double x = g1*fac;
      const double y = g2*fac;
      const double z = g3*fac;

      omesh.push(node3(x,y,z));
      n++;
   }

   // edges, faces
   edge_and_face(nu, nv, omesh);


   // ------------------------
   // create frames
   // ------------------------

   // threads
   kip::threads = 6;

   // scene
   metamesh::kip::scene<> scene;
   scene.resize(1280,1024);

   scene.anti  = anti;
   scene.fov   = 38;
   scene.hzone = 128;
   scene.vzone = 108;
   scene.hsub  = 0;
   scene.vsub  = 0;
   scene.lean  = true;
   scene.sort_min = 10000000;  // qqq eventually remove

   scene.scale   = 0.3;
   scene.edge.on = true;
   scene.face.on = false;
   scene.edge.diameter *= 0.6;
   scene.edge.color(0,0,0);

   /*
   scene.bound.corner.on = true;
   scene.bound.line.on = true;
   */

   // file
   metamesh::image file("output/boy-", 1000, "rgb");

   // parameters: begin, end
   const kip::point<double> onetarget(0.00, 0.00, 0.000);
   const kip::point<double> twotarget(0.07,-0.01,-0.625);
   const double onetheta = -180, twotheta = -111;
   const double onephi   =  +90, twophi   = -258;
   ///const double oned     =  3.5, twod     =  5.0;
   const double oned     =  4.0, twod     =  6.0;

   /*
   std::ofstream ofs("boy.kip");
   metamesh::kip::ostream<double,::kip::rgb> kout(ofs);
   kout.scale   = 0.3;
   kout.edge.on = true;
   kout.face.on = false;
   kout.edge.diameter *= 0.4;
   kout.edge.color(0,0,0);
   kout << omesh;
   */

   // middle mesh; initially set to omesh in order to have the correct
   // number of nodes, and to create edges and faces
   middle = omesh;

   // loop
   const metamesh::loop frame(nframes);
   while (frame()) {
      counter = frame;

      const double fac = nframes <= 1 ? 0 : double(frame)/(nframes-1);
      ///std::cout << "fac == " << fac << std::endl;

      // advance mesh
      metamesh::loop n(omesh.node.size());
      while (n()) {
         const metamesh::point<double> a = imesh.node[n];
         const metamesh::point<double> b = omesh.node[n];
         const metamesh::point<double> c = a + fac*(b-a);
         middle.node[n](c.x, c.y, c.z);
      }

      // rendering parameters
      scene.target = onetarget + fac*(twotarget - onetarget);
      scene.d      = oned      + fac*(twod      - oned     );
      scene.theta  = onetheta  + fac*(twotheta  - onetheta );
      scene.phi    = onephi    + fac*(twophi    - onephi   );

      // light
      scene.light()[0](scene.target, scene.d, scene.theta+60, scene.phi+10);

      // render, putting result in .rgb file
      std::cout << "Frame " << std::size_t(frame) << ":";
      std::cout << " model..."   << std::flush;
      scene << middle;
      std::cout << " render..." << std::flush;
      scene.render();
      std::cout << " write..."  << std::flush;
      file << scene;
      std::cout << std::endl;
   }
}
