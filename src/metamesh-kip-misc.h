/* -*- C++ -*- */

#ifndef METAMESH_KIP_MISC
#define METAMESH_KIP_MISC

// This file provides miscellaneous helper constructs related
// to metamesh's interface to the kip visualization library.

// average: forward declaration
namespace metamesh {
namespace internal {
   template<class MESH, class ELEM>
   inline point<typename MESH::value_t> average(const MESH &, const ELEM &);
}
}



// =============================================================================
// get_location
//    For node: use node's conversion to point.
//    For edge, face, and cell: use the average location of the element's bases.
//    Specialize any of these (say, to use centroid) if you wish.
// location(): forwards to get_location::operator()
// =============================================================================

namespace metamesh {
namespace kip {

// get_location: generic
template<class MESH, class ELEM>
struct get_location {
};



// get_location: node
template<class MESH, class terms, class base>
struct get_location<MESH,metamesh::node<terms,base>> {
   inline metamesh::point<typename MESH::value_t> operator()(
      const MESH &, const metamesh::node<terms,base> &node
   ) const {
      // use node's conversion to point
      return metamesh::point<typename MESH::value_t>(node);
   }
};

// get_location: edge
template<class MESH, class terms, class base>
struct get_location<MESH,metamesh::edge<terms,base>> {
   inline metamesh::point<typename MESH::value_t> operator()(
      const MESH &mesh, const metamesh::edge<terms,base> &edge
   ) const {
      return internal::average(mesh,edge);
   }
};

// get_location: face
template<class MESH, class terms, class base>
struct get_location<MESH,metamesh::face<terms,base>> {
   inline metamesh::point<typename MESH::value_t> operator()(
      const MESH &mesh, const metamesh::face<terms,base> &face
   ) const {
      return internal::average(mesh,face);
   }
};

// get_location: cell
template<class MESH, class terms, class base>
struct get_location<MESH,metamesh::cell<terms,base>> {
   inline metamesh::point<typename MESH::value_t> operator()(
      const MESH &mesh, const metamesh::cell<terms,base> &cell
   ) const {
      return internal::average(mesh,cell);
   }
};



// location
template<class MESH, class ELEM>
inline point<typename MESH::value_t> location(
   const MESH &mesh, const ELEM &elem
) {
   return get_location<MESH,ELEM>()(mesh,elem);
}

}  // kip
}  // metamesh



// =============================================================================
// average
// Helper function
// =============================================================================

namespace metamesh {
namespace internal {

template<class MESH, class ELEM>
inline point<typename MESH::value_t> average(const MESH &mesh, const ELEM &elem)
{
   using real = typename MESH::value_t;

   point<real> sum(real(0), real(0), real(0));
   const std::size_t size = elem.size();
   if (size == 0) return sum;

   const loop i(size);
   while (i())
      sum += metamesh::kip::location(mesh, mesh(elem[i]));

   return sum/real(size);
}

}  // internal
}  // metamesh



// =============================================================================
// bounds_compute
// bounds_line
// bounds_corner
// write_bounds
// =============================================================================

namespace metamesh {
namespace internal {

// bounds_compute
template<
   class real, class base,
   class NODE, class EDGE, class FACE, class CELL, class BASE, std::size_t FORM
>
inline void bounds_compute(
   metamesh::kip::ostream<real,base> &s,
   const mesh<NODE,EDGE,FACE,CELL,BASE,FORM> &mesh
) {
   // initialize
   s.bound.min.x = s.bound.min.y = s.bound.min.z =
      std::numeric_limits<real>::max();
   s.bound.max.x = s.bound.max.y = s.bound.max.z =
      std::numeric_limits<real>::min();

   // nodes
   const loop n(mesh.node);
   while (n()) {
      const point<real> p = mesh.node[n];
      s.bound.min.x = std::min(s.bound.min.x, p.x);
      s.bound.min.y = std::min(s.bound.min.y, p.y);
      s.bound.min.z = std::min(s.bound.min.z, p.z);

      s.bound.max.x = std::max(s.bound.max.x, p.x);
      s.bound.max.y = std::max(s.bound.max.y, p.y);
      s.bound.max.z = std::max(s.bound.max.z, p.z);
   }

   if (!(s.bound.min.x < s.bound.max.x))
      s.bound.min.x = s.bound.max.x = real(0);
   if (!(s.bound.min.y < s.bound.max.y))
      s.bound.min.y = s.bound.max.y = real(0);
   if (!(s.bound.min.z < s.bound.max.z))
      s.bound.min.z = s.bound.max.z = real(0);

   // avg
   s.bound.avg = (s.bound.min + s.bound.max)/real(2);
}



// bounds_line
template<class real, class base>
inline void bounds_line(
   metamesh::kip::ostream<real,base> &s,
   const point<real> &one,
   const point<real> &two, const real &r,
   bool &com
) {
   if (r > 0 && one != two) {
      if (kip_no_or(!s.push(
         ::kip::pill<real,base>(one, two, r, s.bound.line.color)
      ))) {
         if (!com)
            s.stream << "\n// lines\n";
         s.stream
            << "pill("
            <<  one << ", " << two << ", "
            <<  r << ", " << s.bound.line.color << ")\n";
      }
      com = true;
   }
}



// bounds_corner
template<class real, class base>
inline void bounds_corner(
   metamesh::kip::ostream<real,base> &s,
   const point<real> &pnt, const real &r, const base &color,
   bool &com
) {
   if (r > 0) {
      if (kip_no_or(!s.push(
         ::kip::sphere<real,base>(pnt, r, color)
      ))) {
         if (!com)
            s.stream << "\n// corners\n";
         s.stream
            << "sphere("
            <<  pnt << ", " << r << ", " << color << ")\n";
      }
      com = true;
   }
}



// write_bounds
template<class real, class base>
inline void write_bounds(metamesh::kip::ostream<real,base> &stream)
{
   // points
   const point<real>
      a(stream.bound.min.x, stream.bound.min.y, stream.bound.min.z),
      b(stream.bound.max.x, stream.bound.min.y, stream.bound.min.z),
      c(stream.bound.max.x, stream.bound.max.y, stream.bound.min.z),
      d(stream.bound.min.x, stream.bound.max.y, stream.bound.min.z),
      e(stream.bound.min.x, stream.bound.min.y, stream.bound.max.z),
      f(stream.bound.max.x, stream.bound.min.y, stream.bound.max.z),
      g(stream.bound.max.x, stream.bound.max.y, stream.bound.max.z),
      h(stream.bound.min.x, stream.bound.max.y, stream.bound.max.z);

   // lines
   if (stream.bound.line.on) {
      const real r = op::half(stream.scale * stream.bound.line.diameter);
      bool com = false;  // prefix comment iff write something
      bounds_line(stream, a,b,r, com);  bounds_line(stream, b,c,r, com);
      bounds_line(stream, c,d,r, com);  bounds_line(stream, d,a,r, com);
      bounds_line(stream, e,f,r, com);  bounds_line(stream, f,g,r, com);
      bounds_line(stream, g,h,r, com);  bounds_line(stream, h,e,r, com);
      bounds_line(stream, a,e,r, com);  bounds_line(stream, b,f,r, com);
      bounds_line(stream, c,g,r, com);  bounds_line(stream, d,h,r, com);
   }

   // corners
   if (stream.bound.corner.on) {
      const real r = op::half(stream.scale * stream.bound.corner.diameter);
      bool com = false;  // prefix comment iff write something
      bounds_corner(stream, a,r, stream.bound.corner.xmin.ymin.zmin.color, com);
      bounds_corner(stream, b,r, stream.bound.corner.xmax.ymin.zmin.color, com);
      bounds_corner(stream, c,r, stream.bound.corner.xmax.ymax.zmin.color, com);
      bounds_corner(stream, d,r, stream.bound.corner.xmin.ymax.zmin.color, com);
      bounds_corner(stream, e,r, stream.bound.corner.xmin.ymin.zmax.color, com);
      bounds_corner(stream, f,r, stream.bound.corner.xmax.ymin.zmax.color, com);
      bounds_corner(stream, g,r, stream.bound.corner.xmax.ymax.zmax.color, com);
      bounds_corner(stream, h,r, stream.bound.corner.xmin.ymax.zmax.color, com);
   }
}

}  // internal
}  // metamesh



// =============================================================================
// scaling
// =============================================================================

namespace metamesh {
namespace internal {

// ibclass: helper
template<std::size_t n, bool b>
class ibclass { };



// scaling: terminal case
template<class real, class MESH, std::size_t form>
inline void scaling(real &, const MESH &, const ibclass<form,false>)
{
}

// Scaling, based on characteristic "size" of mesh elements of the given form.
// For example, when form == 2, consider faces (2-form mesh elements). Compute
// the average distance between the locations of the constituent parts (either
// nodes or edges) from which faces are defined.
template<class real, class MESH, std::size_t form>
inline void scaling(real &scale, const MESH &mesh, const ibclass<form,true>)
{
   // auto will be std::vector of node<...>, edge, face, or cell
   const auto &elements = mesh.elements(component<form>());

   if (elements.size() > 0) {
      scale = 0;  std::size_t n = 0;
      const metamesh::loop e(elements);
      while (e()) {
         // auto will be node<...>, edge, face, or cell
         const auto &elem = elements[e];
         const metamesh::loop i(elem,true,false);
         while (i()) {
            const point<real> a = kip::location(mesh, mesh(elem[i]));
            const point<real> b = kip::location(mesh, mesh(elem[i+1]));
            scale += mod(b-a);
            n++;
         }
      }
      if (n) scale /= real(n);
   }

   if (scale == 0)
      scaling(scale, mesh, ibclass< form+1, form+1 <= MESH::form >());
}



// scaling_compute(stream,mesh)
template<
   class real, class base,
   class NODE, class EDGE, class FACE, class CELL, class BASE, std::size_t FORM
>
inline void scaling_compute(
   metamesh::kip::ostream<real,base> &stream,
   const mesh<NODE,EDGE,FACE,CELL,BASE,FORM> &mesh
) {
   // Attempt to estimate a reasonable scaling
   real scale = 0;
   scaling(scale, mesh, ibclass<1,1<=FORM>());

   // The present function is called when stream.scale <= 0. The interpretation
   // is as follows. If 0, use the estimated scaling from above. If < 0, use the
   // estimated scaling, times stream.scale. For instance, set stream.scale=-0.5
   // to have scaling set to half the metamesh-estimated value. (In either case,
   // we use 1 for the "estimated scaling" if the estimate somehow failed (=0).)
   stream.scale = std::abs(
      (scale == 0 ? 1 : scale)*(stream.scale == 0 ? 1 : stream.scale)
   );
}

}  // internal
}  // metamesh



// =============================================================================
// consistent
// assignfour
// qqq Martin: Consider a more-generic way of doing stuff like this
// =============================================================================

namespace metamesh {
namespace internal {

// ------------------------
// consistent
// ------------------------

// terminal
template<class MESH, class END, std::size_t n, bool b>
inline bool consistent(const MESH &, const END &, const ibclass<n,b>)
{
   return true;
}

// cell
template<class MESH, class END>
inline bool consistent(const MESH &mesh, const END &end, const ibclass<3,true>)
{
   return
      mesh.cell.size() >= end.cell &&
      consistent(mesh, end, ibclass<4,4<=MESH::form>());
}

// face
template<class MESH, class END>
inline bool consistent(const MESH &mesh, const END &end, const ibclass<2,true>)
{
   return
      mesh.face.size() >= end.face &&
      consistent(mesh, end, ibclass<3,3<=MESH::form>());
}

// edge
template<class MESH, class END>
inline bool consistent(const MESH &mesh, const END &end, const ibclass<1,true>)
{
   return
      mesh.edge.size() >= end.edge &&
      consistent(mesh, end, ibclass<2,2<=MESH::form>());
}

// node
template<class MESH, class END>
inline bool consistent(const MESH &mesh, const END &end, const ibclass<0,true>)
{
   return
      mesh.node.size() >= end.node &&
      consistent(mesh, end, ibclass<1,1<=MESH::form>());
}



// ------------------------
// assignfour
// ------------------------

// terminal
template<class MESH, class END, std::size_t n, bool b>
inline void assignfour(const MESH &, END &, const ibclass<n,b>)
{
   // nothing
}

// cell
template<class MESH, class END>
inline void assignfour(const MESH &mesh, END &end, const ibclass<3,true>)
{
   end.cell = mesh.cell.size();
   assignfour(mesh, end, ibclass<4,4<=MESH::form>());
}

// face
template<class MESH, class END>
inline void assignfour(const MESH &mesh, END &end, const ibclass<2,true>)
{
   end.face = mesh.face.size();
   assignfour(mesh, end, ibclass<3,3<=MESH::form>());
}

// edge
template<class MESH, class END>
inline void assignfour(const MESH &mesh, END &end, const ibclass<1,true>)
{
   end.edge = mesh.edge.size();
   assignfour(mesh, end, ibclass<2,2<=MESH::form>());
}

// node
template<class MESH, class END>
inline void assignfour(const MESH &mesh, END &end, const ibclass<0,true>)
{
   end.node = mesh.node.size();
   assignfour(mesh, end, ibclass<1,1<=MESH::form>());
}

}  // internal
}  // metamesh



// =============================================================================
// mesh_check
// =============================================================================

namespace metamesh {
namespace internal {

// 0-form
template<class OSTREAM, class MESH>
inline bool mesh_check(
   const OSTREAM &stream, const MESH &mesh,
   const iclass<0>, const std::string &context
) {
   return mesh.check(
      context,
      stream.begin.node
   ) != diagnostic_error;
}

// 1-form
template<class OSTREAM, class MESH>
inline bool mesh_check(
   const OSTREAM &stream, const MESH &mesh,
   const iclass<1>, const std::string &context
) {
   return mesh.check(
      context,
      stream.begin.node, stream.begin.edge
   ) != diagnostic_error;
}

// 2-form
template<class OSTREAM, class MESH>
inline bool mesh_check(
   const OSTREAM &stream, const MESH &mesh,
   const iclass<2>, const std::string &context
) {
   return mesh.check(
      context,
      stream.begin.node, stream.begin.edge, stream.begin.face
   ) != diagnostic_error;
}

// 3-form
template<class OSTREAM, class MESH>
inline bool mesh_check(
   const OSTREAM &stream, const MESH &mesh,
   const iclass<3>, const std::string &context
) {
   return mesh.check(
      context,
      stream.begin.node, stream.begin.edge, stream.begin.face, stream.begin.cell
   ) != diagnostic_error;
}

}  // internal
}  // metamesh

#endif
