
#include "kip.h"
#include "metamesh.h"

// number of nodes, number of frames, antialiasing
const std::size_t nu = 120;  // along
const std::size_t nv =  40;  // around
const std::size_t nframes = 100;
const std::size_t anti = 1;

// types
using node2 = metamesh::node<metamesh::cartesian<2>>;
using edge2 = metamesh::edge<metamesh::two  <node2>>;
using face2 = metamesh::face<metamesh::four <node2>>;
using mesh2 = metamesh::mesh<node2,edge2,face2>;

using node3 = metamesh::node<metamesh::cartesian<3>>;
using edge3 = metamesh::edge<metamesh::two  <node3>>;
using face3 = metamesh::face<metamesh::four <node3>>;
using mesh3 = metamesh::mesh<node3,edge3,face3>;



// =============================================================================
// Override node base
// =============================================================================

namespace metamesh {
namespace kip {

template<class OSTREAM>
struct write_node_base<OSTREAM,mesh3,node3,node3::base_t> {
   inline OSTREAM &operator()(
      OSTREAM &stream,
      const mesh3 &mesh, const node3 &node, const node3::base_t &
   ) {
      const std::size_t n = std::size_t(&node - &mesh.node[0]);
      const std::size_t i = n % nu;
      const std::size_t j = n / nu;

      if (i == 0 || j == 0 || i == nu-1 || j == nv-1) {
         stream.node.diameter = 0.5*double(internal::default_node_diameter*1.01);
         stream.node.color = rgb(0,0,0);
      } else {
         stream.node.diameter = 0.5*double(internal::default_node_diameter);

         const double usigma = double(nu)/2, du = (double(i)-usigma)/usigma;
         const double vsigma = double(nv)/2, dv = (double(j)-vsigma)/vsigma;
         const double exp = 255*std::exp(-(du*du + dv*dv));

         using uchar = unsigned char;
         const uchar r = uchar(256*i/nu);
         const uchar g = uchar(256*j/nv);
         const uchar b = uchar(exp);
         stream.node.color = rgb(r,g,b);
      }

      return stream;
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

   const metamesh::loop ix(nu,true,false);
   const metamesh::loop jx(nv);
   const metamesh::loop iy(nu);
   const metamesh::loop jy(nv,true,false);

   // x-direction edges
   while (ix())
   while (jx()) {
      const std::size_t n = nu*jx+ix;
      mesh.push(edge((metamesh::tup, n, n+1)));
   }

   // y-direction edges
   while (iy())
   while (jy()) {
      const std::size_t n = nu*jy+iy;
      mesh.push(edge((metamesh::tup, n, n+nu)));
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
   // meshes
   mesh2 imesh;
   mesh3 omesh, middle;


   // ------------------------
   // mesh: input
   // ------------------------

   const double pi = double(metamesh::pi);
   const double umin = -0.4*pi, umax = +0.5*pi;
   const double vmin = +0.2*pi, vmax = +1.2*pi;

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
      const double u = (imesh.node[n].x - umin)*  pi/(umax-umin);
      const double v = (imesh.node[n].y - vmin)*2*pi/(vmax-vmin);

      const double x = -2.0/15*cos(u)*(
         3*cos(v) -
        30*sin(u) +
        90*pow(cos(u),4)*sin(u) -
        60*pow(cos(u),6)*sin(u) +
         5*cos(u)*cos(v)*sin(u)
      );

      const double y = -1.0/15*sin(u)*(
         3*cos(v) -
         3*pow(cos(u),2)*cos(v) -
        48*pow(cos(u),4)*cos(v) +
        48*pow(cos(u),6)*cos(v) -
        60*sin(u) +
         5*cos(u)*cos(v)*sin(u) -
         5*pow(cos(u),3)*cos(v)*sin(u) -
        80*pow(cos(u),5)*cos(v)*sin(u) +
        80*pow(cos(u),7)*cos(v)*sin(u)
      );

      const double z = 2.0/15*(3 + 5*cos(u)*sin(u))*sin(v) + 2.0;

      omesh.push(node3(x,y,z));
      n++;
   }

   // edges, faces
   edge_and_face(nu, nv, omesh);


   // ------------------------
   // create frames
   // ------------------------

   // threads
   kip::threads = 4;

   // scene
   metamesh::kip::scene<> scene;
   scene.resize(1280,1024);

   scene.anti  = anti;
   scene.fov   = 48;
   scene.hzone = 240;
   scene.vzone = 108;
   scene.hsub  = 4;
   scene.vsub  = 4;
   scene.lean  = true;
   scene.sort_min = 10000000;  // qqq eventually remove
   scene.scale   = 0.8;
   scene.edge.on = false;
   scene.face.on = false;

   // file
   metamesh::image file("output/klein-", 1000, "rgb");

   // parameters: begin, end
   const kip::point<double> onetarget(0.15708, 2.19911, -0.4);
   const kip::point<double> twotarget(0.15296, 2.10257,  1.6);
   const double onetheta = 0;
   const double twotheta = 360.0;
   const double onephi = 40;  const double oned = 4.5;
   const double twophi = 50;  const double twod = 5.6;

   // middle mesh; initially set to omesh in order to have the correct
   // number of nodes, and to create edges and faces
   middle = omesh;

   // loop
   const metamesh::loop frame(nframes);
   while (frame()) {
      const double fac = nframes == 1 ? 0 : double(frame)/(nframes-1);

      // advance mesh
      metamesh::loop n(omesh.node.size());
      while (n()) {
         const metamesh::point<double> a = imesh.node[n];
         const metamesh::point<double> b = omesh.node[n];
         const metamesh::point<double> c = a + fac*(b-a);
         middle.node[n](c.x, c.y, c.z);
      }
      ///std::cout << scene.bound.average << std::endl;

      // set rendering parameters
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
