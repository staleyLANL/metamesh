/* -*- C++ -*- */

#ifndef METAMESH_KIP_WRITE
#define METAMESH_KIP_WRITE

// This file provides functions for writing mesh constructs to kip format,
// where kip is the author's rendering library.



// =============================================================================
// Mesh base
// write_mesh_base(ostream, mesh, base)
// =============================================================================

namespace metamesh {
namespace kip {

template<class OSTREAM, class MESH, class BASE>
struct write_mesh_base {
   inline OSTREAM &operator()(
      OSTREAM &kstream,
      const MESH &, const BASE &
   ) const {
      // Consider the following if writing something...
      // if (kip_no_or(!s.has_scene())) {
      //    internal::write_comment(kstream.stream, "base", 27);
      // }
      return kstream;
   }
};

}  // kip
}  // metamesh



// =============================================================================
// Element base
// Empty; metamesh has no knowledge of a user's element-base type.
//
// write_node_base(ostream, mesh, node, base)
// write_edge_base(ostream, mesh, edge, base)
// write_face_base(ostream, mesh, face, base)
// write_cell_base(ostream, mesh, cell, base)
// =============================================================================

namespace metamesh {
namespace kip {

// write_node_base
template<class OSTREAM, class MESH, class NODE, class BASE>
struct write_node_base {
   inline OSTREAM &operator()(
      OSTREAM &stream, const MESH &, const NODE &, const BASE &
   ) const {
      return stream;
   }
};

// write_edge_base
template<class OSTREAM, class MESH, class EDGE, class BASE>
struct write_edge_base {
   inline OSTREAM &operator()(
      OSTREAM &stream, const MESH &, const EDGE &, const BASE &
   ) const {
      return stream;
   }
};

// write_face_base
template<class OSTREAM, class MESH, class FACE, class BASE>
struct write_face_base {
   inline OSTREAM &operator()(
      OSTREAM &stream, const MESH &, const FACE &, const BASE &
   ) const {
      return stream;
   }
};

// write_cell_base
template<class OSTREAM, class MESH, class CELL, class BASE>
struct write_cell_base {
   inline OSTREAM &operator()(
      OSTREAM &stream, const MESH &, const CELL &, const BASE &
   ) const {
      return stream;
   }
};

}  // kip
}  // metamesh



// =============================================================================
// Element
// Simple, reasonable shapes.
//
// write_node(ostream, mesh, node)
// write_edge(ostream, mesh, edge)
// write_face(ostream, mesh, face)
// write_cell(ostream, mesh, cell)
// =============================================================================

namespace metamesh {
namespace kip {

// write_node
template<class OSTREAM, class MESH, class NODE>
struct write_node {
   inline OSTREAM &operator()(
      OSTREAM &s, const MESH &mesh, const NODE &node
   ) const {
      // types
      using real = typename OSTREAM::real_t;
      #if defined(KIP_RENDERER)
      using base = typename OSTREAM::base_t;
      #endif

      // on
      if (!s.on) return s;
      if (!s.node.on) return s;

      // radius
      const real r = op::half(std::abs(s.scale * s.node.diameter));
      if (r == real(0)) return s;

      // center
      const point<real> c(location(mesh,node));

      // node
      if (kip_no_or(!s.push(
         ::kip::sphere<real,base>(c, r, s.node.color)
      ))) {
         s.stream
            << "sphere("
            <<  c << ", " << r << ", " << s.node.color << ")\n";
      }

      // done
      return s;
   }
};



// write_edge
template<class OSTREAM, class MESH, class EDGE>
struct write_edge {
   inline OSTREAM &operator()(
      OSTREAM &s, const MESH &mesh, const EDGE &edge
   ) const {
      // types
      using real = typename OSTREAM::real_t;
      #if defined(KIP_RENDERER)
      using base = typename OSTREAM::base_t;
      #endif

      // on
      if (!s.on) return s;
      if (!s.edge.on) return s;

      // size (#bases)
      if (edge.size() < 2) return s;

      // radius
      const real r = op::half(std::abs(s.scale * s.edge.diameter));
      if (r == real(0)) return s;

      // begin/end
      const real a = std::abs(s.scale) * s.edge.begin;
      const real b = std::abs(s.scale) * s.edge.end;

      // edge
      const loop i(edge,true,false);
      while (i()) {
         const point<real> from = location(mesh, mesh(edge[i  ]));
         const point<real> to   = location(mesh, mesh(edge[i+1]));
         const point<real> diff = normalize(to - from);

         const point<real> one  = from + a*diff;
         const point<real> two  = to   - b*diff;

         if (one != two) {
            if (kip_no_or(!s.push(
               ::kip::pill<real,base>(one, two, r, s.edge.color)
            ))) {
               s.stream
                  << "pill("
                  <<  one << ", " << two << ", "
                  <<  r << ", " << s.edge.color << ")\n";
            }
         }
      }

      // done
      return s;
   }
};



// write_face
template<class OSTREAM, class MESH, class FACE>
struct write_face {
   inline OSTREAM &operator()(
      OSTREAM &s, const MESH &mesh, const FACE &face
   ) const {
      // types
      using real = typename OSTREAM::real_t;
      #if defined(KIP_RENDERER)
      using base = typename OSTREAM::base_t;
      #endif

      // on
      if (!s.on) return s;
      if (!s.face.on) return s;

      // size (#bases)
      const std::size_t size = face.size();
      if (size < 3) return s;

      // radius
      const real r = op::half(std::abs(s.scale * s.face.diameter));
      if (r == real(0)) return s;

      // half-thickness
      const real h = op::half(std::abs(s.scale * s.face.length));
      if (h == real(0)) return s;

      const point<real> loc = location(mesh, face);
      point<real> sum(real(0), real(0), real(0));

      const loop i(face);
      while (i()) {
         const point<real> a = location(mesh, mesh(face[(i+0) % size]));
         const point<real> b = location(mesh, mesh(face[(i+1) % size]));
         const point<real> c = location(mesh, mesh(face[(i+2) % size]));
         sum += cross(b-a,c-b);
      }
      sum = normalize(sum);
      if (sum == point<real>(real(0),real(0),real(0)))
         return s;

      if (kip_no_or(!s.push(
         ::kip::spheroid<real,base>(loc-h*sum, loc+h*sum, r, s.face.color)
      ))) {
         s.stream
            << "spheroid("
            <<  loc - h*sum << ", "
            <<  loc + h*sum << ", " << r << ", " << s.face.color << ")\n";
      }

      // done
      return s;
   }
};



// write_cell
template<class OSTREAM, class MESH, class CELL>
struct write_cell {
   inline OSTREAM &operator()(
      OSTREAM &s, const MESH &mesh, const CELL &cell
   ) const {
      // types
      using real = typename OSTREAM::real_t;
      #if defined(KIP_RENDERER)
      using base = typename OSTREAM::base_t;
      #endif

      // on
      if (!s.on) return s;
      if (!s.cell.on) return s;

      // radius
      const point<real> r = real(0.5) * std::abs(s.scale) * s.cell.size;
      if (r.x == real(0) || r.y == real(0) || r.z == real(0)) return s;

      // center
      const point<real> c(location(mesh,cell));

      // cell
      if (kip_no_or(!s.push(
         ::kip::box<real,base>(c, s.cell.angle, r, s.cell.color)
      ))) {
         s.stream
            << "box("
            <<  c << ", " << s.cell.angle << ", " << r << ", "
            <<  s.cell.color << ")\n";
      }

      // done
      return s;
   }
};

}  // kip
}  // metamesh



// =============================================================================
// Element connection
// Simple, reasonable shapes.
//
// write_edge_link(ostream, mesh, edge, #)
// write_face_link(ostream, mesh, face, #)
// write_cell_link(ostream, mesh, cell, #)
// =============================================================================

namespace metamesh {
namespace kip {

// write_edge_link
template<class OSTREAM, class MESH, class EDGE>
struct write_edge_link {
   inline OSTREAM &operator()(
      OSTREAM &s, const MESH &mesh, const EDGE &edge, const std::size_t i
   ) const {
      // types
      using real = typename OSTREAM::real_t;
      #if defined(KIP_RENDERER)
      using base = typename OSTREAM::base_t;
      #endif

      // on
      if (!s.on) return s;
      if (!s.edge.link.floor.on && !s.edge.link.arrow.on) return s;

      // size (#bases)
      if (edge.size() < 2) return s;

      // begin to end, normalized
      const point<real> from = location(mesh, edge);
      const point<real> to   = location(mesh, mesh(edge[i]));
      const point<real> diff = normalize(to - from);
      if (diff == point<real>(real(0), real(0), real(0))) return s;

      // node adjustment
      const real rnode = !s.node.on
         ? real(0) : op::half(std::abs(s.scale * s.node.diameter));
      const real redge = !s.edge.on
         ? real(0) : op::half(std::abs(s.scale * s.edge.diameter));
      const real tweak = (rnode < redge)
         ? real(0) : std::sqrt(op::square(rnode) - op::square(redge));

      // edge begin
      if (s.edge.link.floor.on && i == 0) {
         // radius, thickness
         const real r = op::half(std::abs(s.scale*s.edge.link.floor.diameter));
         const real t = std::abs(s.scale*s.edge.link.floor.length);

         if (r != real(0) && t != real(0)) {
            const point<real> a = to - (tweak  )*diff;
            const point<real> b = to - (tweak+t)*diff;
            if (a != b) {
               if (kip_no_or(!s.push(
                  ::kip::cylinder<real,base>(a, b, r, s.edge.link.floor.color)
               ))) {
                  s.stream
                     << "cylinder("
                     <<  a << ", " << b << ", "
                     <<  r << ", " << s.edge.link.floor.color << ")\n";
               }
            }
         }
      }

      // edge end
      if (s.edge.link.arrow.on && i == edge.size()-1) {
         // radius, thickness
         const real r = op::half(std::abs(s.scale*s.edge.link.arrow.diameter));
         const real t = std::abs(s.scale*s.edge.link.arrow.length);

         if (r != real(0) && t != real(0)) {
            const point<real> a = to - (rnode  )*diff;
            const point<real> b = to - (rnode+t)*diff;
            if (a != b) {
               if (kip_no_or(!s.push(
                  ::kip::cone<real,base>(a, b, r, s.edge.link.arrow.color)
               ))) {
                  s.stream
                     << "cone("
                     <<  a << ", " << b << ", "
                     <<  r << ", " << s.edge.link.arrow.color << ")\n";
               }
            }
         }
      }

      // done
      return s;
   }
};



// write_face_link
template<class OSTREAM, class MESH, class FACE>
struct write_face_link {
   inline OSTREAM &operator()(
      OSTREAM &s, const MESH &mesh, const FACE &face, const std::size_t i
   ) const {
      // types
      using real = typename OSTREAM::real_t;
      #if defined(KIP_RENDERER)
      using base = typename OSTREAM::base_t;
      #endif

      // on
      if (!s.on) return s;
      if (!s.face.link.on) return s;

      // radius
      const real r = op::half(std::abs(s.scale * s.face.link.diameter));
      if (r == real(0)) return s;

      // begin/end
      const real a = std::abs(s.scale) * s.face.link.begin;
      const real b = std::abs(s.scale) * s.face.link.end;

      // link
      const point<real> from = location(mesh, face);
      const point<real> to   = location(mesh, mesh(face[i]));
      const point<real> diff = normalize(to - from);
      const point<real> one  = from + a*diff;
      const point<real> two  = to   - b*diff;

      if (one != two) {
         if (kip_no_or(!s.push(
            ::kip::pill<real,base>(one, two, r, s.face.link.color)
         ))) {
            s.stream
               << "pill("
               <<  one << ", " << two << ", "
               <<  r << ", " << s.face.link.color << ")\n";
         }
      }

      // done
      return s;
   }
};



// write_cell_link
template<class OSTREAM, class MESH, class CELL>
struct write_cell_link {
   inline OSTREAM &operator()(
      OSTREAM &s, const MESH &mesh, const CELL &cell, const std::size_t i
   ) const {
      // types
      using real = typename OSTREAM::real_t;
      #if defined(KIP_RENDERER)
      using base = typename OSTREAM::base_t;
      #endif

      // on
      if (!s.on) return s;
      if (!s.cell.link.on) return s;

      // radius
      const real r = op::half(std::abs(s.scale * s.cell.link.diameter));
      if (r == real(0)) return s;

      // begin/end
      const real a = std::abs(s.scale) * s.cell.link.begin;
      const real b = std::abs(s.scale) * s.cell.link.end;

      // link
      const point<real> from = location(mesh, cell);
      const point<real> to   = location(mesh, mesh(cell[i]));
      const point<real> diff = normalize(to - from);
      const point<real> one  = from + a*diff;
      const point<real> two  = to   - b*diff;

      if (one != two) {
         if (kip_no_or(!s.push(
            ::kip::pill<real,base>(one, two, r, s.cell.link.color)
         ))) {
            s.stream
               << "pill("
               <<  one << ", " << two << ", "
               <<  r << ", " << s.cell.link.color << ")\n";
         }
      }

      // done
      return s;
   }
};

}  // kip
}  // metamesh



// =============================================================================
// write_form
// =============================================================================

namespace metamesh {
namespace internal {

// n-form: terminal case
template<class OSTREAM, class MESH, std::size_t n, bool b>
inline void write_form(
   OSTREAM &, const MESH &, const ibclass<n,b>,
   const std::string &
) {
}



// 3-form
template<class OSTREAM, class MESH>
inline void write_form(
   OSTREAM &s, const MESH &mesh, const ibclass<3,true>,
   const std::string &during
) {
   // std::cout << "s.begin.cell == " << s.begin.cell << std::endl;

   if (s.cell.base.on || s.cell.on || s.cell.link.on) {
      // comment
      if (kip_no_or(!s.has_scene())) {
         internal::write_comment(s.stream, "cells", 27);
         s.stream << "\n";
      }

      // bases, cells, links
      const loop c(mesh.cell, s.begin.cell, std::size_t(0));
      while (c()) {
         if (s.cell.base.on) {
            metamesh::kip::write_cell_base<
               OSTREAM, MESH,
               typename MESH::cell_t, typename MESH::cell_t::base_t
            >()(s, mesh, mesh.cell[c], mesh.cell[c].base());
         }

         if (s.cell.on) {
            metamesh::kip::write_cell<
               OSTREAM, MESH,
               typename MESH::cell_t
            >()(s, mesh, mesh.cell[c]);
         }

         if (s.cell.link.on) {
            const loop i(mesh.cell[c]);
            while (i()) {
               metamesh::kip::write_cell_link<
                  OSTREAM, MESH,
                  typename MESH::cell_t
               >()(s, mesh, mesh.cell[c], i);
            }
         }
      }
   }

   // any errors?
   if (!s.stream) {
      error("Problem encountered while writing cells", during);
      return;
   }

   // higher-form, if applicable
   internal::write_form(s, mesh, internal::ibclass<4,4<=MESH::form>(), during);
}



// 2-form
template<class OSTREAM, class MESH>
inline void write_form(
   OSTREAM &s, const MESH &mesh, const ibclass<2,true>,
   const std::string &during
) {
   // std::cout << "s.begin.face == " << s.begin.face << std::endl;

   if (s.face.base.on || s.face.on || s.face.link.on) {
      // comment
      if (kip_no_or(!s.has_scene())) {
         internal::write_comment(s.stream, "faces", 27);
         s.stream << "\n";
      }

      // bases, faces, links
      const loop f(mesh.face, s.begin.face, std::size_t(0));
      while (f()) {
         if (s.face.base.on) {
            metamesh::kip::write_face_base<
               OSTREAM, MESH,
               typename MESH::face_t, typename MESH::face_t::base_t
            >()(s, mesh, mesh.face[f], mesh.face[f].base());
         }

         if (s.face.on) {
            metamesh::kip::write_face<
               OSTREAM, MESH,
               typename MESH::face_t
            >()(s, mesh, mesh.face[f]);
         }

         if (s.face.link.on) {
            const loop i(mesh.face[f]);
            while (i()) {
               metamesh::kip::write_face_link<
                  OSTREAM, MESH,
                  typename MESH::face_t
               >()(s, mesh, mesh.face[f], i);
            }
         }
      }
   }

   // any errors?
   if (!s.stream) {
      error("Problem encountered while writing faces", during);
      return;
   }

   // higher-form, if applicable
   internal::write_form(s, mesh, internal::ibclass<3,3<=MESH::form>(), during);
}



// 1-form
template<class OSTREAM, class MESH>
inline void write_form(
   OSTREAM &s, const MESH &mesh, const ibclass<1,true>,
   const std::string &during
) {
   // std::cout << "s.begin.edge == " << s.begin.edge << std::endl;

   if (s.edge.base.on || s.edge.on ||
       s.edge.link.floor.on || s.edge.link.arrow.on) {

      // comment
      if (kip_no_or(!s.has_scene())) {
         internal::write_comment(s.stream, "edges", 27);
         s.stream << "\n";
      }

      // bases, edges, links
      const loop e(mesh.edge, s.begin.edge, std::size_t(0));
      while (e()) {
         if (s.edge.base.on) {
            metamesh::kip::write_edge_base<
               OSTREAM, MESH,
               typename MESH::edge_t, typename MESH::edge_t::base_t
            >()(s, mesh, mesh.edge[e], mesh.edge[e].base());
         }

         if (s.edge.on) {
            metamesh::kip::write_edge<
               OSTREAM, MESH,
               typename MESH::edge_t
            >()(s, mesh, mesh.edge[e]);
         }

         if (s.edge.link.floor.on || s.edge.link.arrow.on) {
            const loop i(mesh.edge[e]);
            while (i()) {
               metamesh::kip::write_edge_link<
                  OSTREAM, MESH, typename MESH::edge_t
               >()(s, mesh, mesh.edge[e], i);
            }
         }
      }
   }

   // any errors?
   if (!s.stream) {
      error("Problem encountered while writing edges", during);
      return;
   }

   // higher-form, if applicable
   internal::write_form(s, mesh, internal::ibclass<2,2<=MESH::form>(), during);
}



// 0-form
template<class OSTREAM, class MESH>
inline void write_form(
   OSTREAM &s, const MESH &mesh, const ibclass<0,true>,
   const std::string &during
) {
   // std::cout << "s.begin.node == " << s.begin.node << std::endl;

   if (s.node.base.on || s.node.on) {
      // comment
      if (kip_no_or(!s.has_scene())) {
         internal::write_comment(s.stream, "nodes", 27);
         s.stream << "\n";
      }

      // bases, nodes
      // links N/A; nodes aren't defined via smaller-dimensional elements
      const loop n(mesh.node, s.begin.node, std::size_t(0));
      while (n()) {
         if (s.node.base.on) {
            metamesh::kip::write_node_base<
               OSTREAM, MESH,
               typename MESH::node_t, typename MESH::node_t::base_t
            >()(s, mesh, mesh.node[n], mesh.node[n].base());
         }

         if (s.node.on) {
            metamesh::kip::write_node<
               OSTREAM, MESH,
               typename MESH::node_t
            >()(s, mesh, mesh.node[n]);
         }
      }
   }

   // any errors?
   if (!s.stream) {
      error("Problem encountered while writing nodes", during);
      return;
   }

   // higher-form, if applicable
   internal::write_form(s, mesh, internal::ibclass<1,1<=MESH::form>(), during);
}

}  // internal
}  // metamesh



// =============================================================================
// Mesh
// write_mesh(ostream, mesh)
// =============================================================================

namespace metamesh {
namespace kip {

template<class OSTREAM, class MESH>
struct write_mesh {
   inline OSTREAM &operator()(
      OSTREAM &kstream, const MESH &mesh, const std::string &during
   ) const {
      // on
      if (!kstream.on)
         return kstream;

      // begin
      if (kip_no_or(!kstream.has_scene()))
         internal::write_comment(kstream.stream, "mesh: begin", 80);

      // scaling
      if (kstream.scale <= 0)
         internal::scaling_compute(kstream,mesh);

      // base
      if (kstream.base.on) {
         write_mesh_base<
            OSTREAM, MESH, typename MESH::base_t
         >()(kstream, mesh, mesh.base());
         if (!kstream.stream)
            error("Problem encountered while writing mesh base", during);
      }

      // cells: bases, cells, links
      // faces: bases, faces, links
      // edges: bases, edges, links
      // nodes: bases, nodes
      if (kstream.stream)
         internal::write_form(
            kstream, mesh, internal::ibclass<0,true>(), during);

      // bounds
      if (kstream.stream) {
         // on?
         const bool bound_on = kstream.bound.line.on || kstream.bound.corner.on;

         // compute?
         if (bound_on || kstream.bound.compute)
            internal::bounds_compute(kstream,mesh);

         // write?
         if (bound_on) {
            if (kip_no_or(!kstream.has_scene()))
               internal::write_comment(kstream.stream, "bounding box", 27);
            internal::write_bounds(kstream);
            if (!kstream.stream)
               error("Problem encountered while writing bounding box", during);
         }
      }

      // done
      if (kip_no_or(!kstream.has_scene()))
         internal::write_comment(kstream.stream, "mesh: end", 80);
      return kstream;
   }
};

}  // kip
}  // metamesh



// =============================================================================
// metamesh::kip::ostream << mesh
// =============================================================================

/*
Calls:

   write_mesh         (ostream, mesh)

Which in turn calls:

   write_mesh_base    (ostream, mesh, base)
   node
      write_node_base (ostream, mesh, node, base)
      write_node      (ostream, mesh, node)
   edge
      write_edge_base (ostream, mesh, edge, base)
      write_edge      (ostream, mesh, edge)
      write_edge_link (ostream, mesh, edge, #)
   face
      write_face_base (ostream, mesh, face, base)
      write_face      (ostream, mesh, face)
      write_face_link (ostream, mesh, face, #)
   cell
      write_cell_base (ostream, mesh, cell, base)
      write_cell      (ostream, mesh, cell)
      write_cell_link (ostream, mesh, cell, #)
   write_bounds
*/

namespace metamesh {
namespace kip {

template<
   class real, class base,
   class NODE, class EDGE, class FACE, class CELL, class BASE, std::size_t FORM
>
metamesh::kip::ostream<real,base> &operator<<(
   metamesh::kip::ostream<real,base> &kstream,
   const mesh<NODE,EDGE,FACE,CELL,BASE,FORM> &mesh
) {
   (void)kstream;
   (void)mesh;

   // ------------------------
   // check
   // ------------------------

   static const std::string
      before = "Detected in mesh.check() call within kip::ostream << mesh",
      during = "Detected during kip::ostream << mesh";

   if (!kstream.stream) {
      error("kip::ostream's wrapped std::ostream is in a fail state", during);
      return kstream;
   }

   // ------------------------
   // proceed-mode logic
   // ------------------------

   // types
   using OSTREAM = metamesh::kip::ostream<real,base>;
   using MESH    = metamesh::mesh<NODE,EDGE,FACE,CELL,BASE,FORM>;

   // previous-call information
   static struct {
      const OSTREAM *stream = nullptr;  std::size_t node = 0, edge = 0;
      const MESH    *mesh   = nullptr;  std::size_t face = 0, cell = 0;
   } end;

   // flag: should we start just beyond where we appear to have finished
   // on the previous call, or start from the beginning?
   const bool Continue =
      kstream.proceed        &&  // proceed mode on
      &kstream == end.stream &&  // arguably the same stream
      &mesh    == end.mesh   &&  // arguably the same mesh...and with more...
      internal::consistent(mesh,end,internal::ibclass<0,true>());  // elements

   kstream.begin.node = Continue ? end.node : 0;
   kstream.begin.edge = Continue ? end.edge : 0;
   kstream.begin.face = Continue ? end.face : 0;
   kstream.begin.cell = Continue ? end.cell : 0;

   // Update previous-call information, for possible use on the next call to
   // this function. Note that we must always do this, regardless of the values
   // of kstream.proceed and Continue, as those might be true on the next call.
   end.stream = &kstream;
   end.mesh   = &mesh;
   internal::assignfour(mesh,end,internal::ibclass<0,true>());

   // ------------------------
   // write
   // ------------------------

   // Note: mesh_check() is done here, not earlier, because it uses
   // kstream.begin (computed above).
   if (internal::mesh_check(kstream, mesh, iclass<MESH::form>(), before)) {
      if (kip_no_or(!kstream.has_scene()))
         kstream.highlighting();
      write_mesh<OSTREAM,MESH>()(kstream, mesh, during);
   }

   kstream.stream << std::flush;
   return kstream;
}

}  // kip
}  // metamesh

#endif
