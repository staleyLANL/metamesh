/* -*- C++ -*- */

#ifndef METAMESH_NEFC
#define METAMESH_NEFC

// This file provides miscellaneous helper functionality that's needed
// by the node, edge, face, and cell classes.



// =============================================================================
// Some forward declarations
// =============================================================================

namespace metamesh {

// edge, face, cell
// Declare class, operator>>, and operator<<
#define metamesh_make_io(nefc)\
   template<class terms, class base, std::size_t dimension>\
   class nefc;\
   \
   template<class terms, class base, std::size_t dimension>\
   std::istream &operator>>(\
      std::istream &,       metamesh::nefc<terms,base,dimension> &);\
   \
   template<class terms, class base, std::size_t dimension>\
   std::ostream &operator<<(\
      std::ostream &, const metamesh::nefc<terms,base,dimension> &);

   metamesh_make_io(node)
   metamesh_make_io(edge)
   metamesh_make_io(face)
   metamesh_make_io(cell)
#undef metamesh_make_io


// mesh
// Declare class
template<
   class  node,
   class  edge,
   class  face,
   class  cell,
   class  base,  // base, as with other types
   std::size_t form   // will be computed from the other template parameters
> class mesh;

}  // metamesh



// =============================================================================
// check_index
// Used by edge, face, and cell
// =============================================================================

namespace metamesh {
namespace internal {

// This function checks that an index in an edge, face, or cell is in range.
// That's an easy check, and so in fact the main purpose of this function is
// to construct and emit a sensible diagnostic if the index is not in range.
//
// Example. Consider a face that's based on edges. In this case, face[i] is
// being examined somewhere. The value i is sent here only for error-message
// printing; other needed information is sent separately.
//
// The second argument, ibasis, is a particular edge-index of face[i]; don't
// confuse i (the face index) with ibasis (one of its edge indexes). ibasis
// is the number of edges in an edge container somewhere. ibasis, then, must
// be less than nbasis. form_name would be "face", basis_name "edge", and
// context would be any applicable context for any error message.

template<class basis, class index>
diagnostic_t check_index(
   const std::size_t i,
   const index_to<basis,index> ibasis,  // wraps an index; see index_to
   const std::size_t nbasis,
   const std::string &form_name,
   const std::string &basis_name,
   const std::string &context
) {
   const index to = index(ibasis);
   if (to < nbasis) return diagnostic_good;

   std::ostringstream err, ctx;
   err <<  basis_name << " index = " << to << "; must be < " << nbasis;
   ctx << "Detected during " << form_name << ".check's examination of "
       << "index [" << i << ']';

   return error(err, new_context(ctx.str(),context));
}

}  // internal
}  // metamesh



// =============================================================================
// node_coord (i/o, with error printing, of node coordinate)
// node_base  (i/o, with error printing, of node base)
// node_check (check, with error printing, of i/o'd node)
//
// Two variants (istream, ostream) of each
// =============================================================================

namespace metamesh {
namespace internal {

// ------------------------
// node_coord
// ------------------------

// input
// Read an individual node coordinate, e.g. x in an (x,y,z) node. These are
// often floating-point numbers, hence the template<class real> terminology,
// but could in principle be any suitable type.
template<class real>
bool node_coord(
   std::istream &s, real &value,
   const std::string &label  // coordinate's name, e.g. "x"
) {
   if (s >> value) return true;

   std::ostringstream oss;
   oss << "Could not read " << label << " coordinate";
   error(oss, "Detected during istream >> node");

   return false;
}


// output
// Write an individual node coordinate.
template<class real>
bool node_coord(
   std::ostream &s, const real &value,
   const std::string &label
) {
   if (s << value) return true;

   std::ostringstream oss;
   oss << "Could not write " << label << " coordinate";
   error(oss, "Detected during ostream << node");

   return false;
}



// ------------------------
// node_base
// ------------------------

// input
template<class base>
bool node_base(
   std::istream &s, base &value
) {
   if (s >> value) return true;
   error("Could not read base", "Detected during istream >> node");
   return false;
}


// output
// Designed to sensibly handle 0d nodes (which would have had no "coordinate"
// values printed immediately prior to this "base" printing), as well as nodes
// of greater dimension (which would have had such printing). Also designed
// to handle "base" values with no-op printing (e.g., our default "stub" base),
// plus ones that do print something (for example, a user-defined base that
// contains velocities or pressures). See comments.
template<class base>
bool node_base(
   std::ostream &s, const base &value, const bool zero_d = false
) {
   if (zero_d) {
      // For "empty" bases, nothing will print
      if (s << value) return true;
   } else {
      // For "empty" bases, nothing will print; otherwise, three spaces will
      // separate anything that does print from the earlier coordinate printing
      std::ostringstream buf;
      buf << value;
      if (buf && (buf.str() == "" || s << "   " << buf.str())) return true;
   }

   error("Could not write base", "Detected during ostream << node");
   return false;
}



// ------------------------
// node_check
// ------------------------

// Both of these just conveniently package node.check() calls, with an
// appropriate context argument, and provide a handy bool return value.
// Both return false if, and only if, there's a definite error.

// called after input
// istream unused; distinguishes function from the one below
template<class terms, class base, std::size_t dimension>
inline bool node_check(
   const std::istream &,
   const node<terms,base,dimension> &obj
) {
   return
      obj.check("Detected in node.check call after istream >> node") !=
      diagnostic_error;
}


// called before output
// ostream unused; distinguishes function from the one above
template<class terms, class base, std::size_t dimension>
inline bool node_check(
   const std::ostream &,
   const node<terms,base,dimension> &obj
) {
   return
      obj.check("Detected in node.check call before ostream << node") !=
      diagnostic_error;
}

}  // internal
}  // metamesh



// =============================================================================
// check_elements
// Call check() for each element (node, edge, face, or cell, in this context)
// of a container, starting at position pos.
// =============================================================================

namespace metamesh {
namespace internal {

// For nodes
// No "nbasis" (as for the check_index() function) here
template<class CONTAINER>
diagnostic_t check_elements(
   const CONTAINER &vec,
   const std::size_t pos,
   const std::string &label,
   const std::string &context
) {
   diagnostic_t rv = diagnostic_good;  // so far
   const std::size_t size = vec.size();

   for (std::size_t i = pos;  i < size;  ++i) {
      std::ostringstream oss;
      oss << "Detected during mesh.check's examination of " << label
          << " [" << i << ']';

      // min, because in diagnostic_t, error < warning < note < good
      rv = metamesh::min(
         rv,
         vec[i].check(new_context(oss.str(),context))  // node check: no nbasis
      );
   }
   return rv;
}



// For edges, faces, and cells
// Has "nbasis" (see remarks describing the check_index() function)
template<class CONTAINER>
diagnostic_t check_elements(
   const CONTAINER &vec,
   const std::size_t pos,
   const std::string &label,
   const std::string &context,
   const std::size_t nbasis
) {
   diagnostic_t rv = diagnostic_good;  // so far
   const std::size_t size = vec.size();

   for (std::size_t i = pos;  i < size;  ++i) {
      std::ostringstream oss;
      oss << "Detected during mesh.check's examination of " << label
          << " [" << i << ']';

      // min, because in diagnostic_t, error < warning < note < good
      rv = metamesh::min(
         rv,
         vec[i].check(nbasis, new_context(oss.str(),context))  // nbasis here
      );
   }
   return rv;
}

}  // internal
}  // metamesh



// =============================================================================
// element_container_read
// element_container_write
//
// An "element" is a node, an edge, a face, or a cell.
// These functions read and write containers of elements.
// =============================================================================

namespace metamesh {
namespace internal {

// element_container_read
template<class CONTAINER>
bool element_container_read(
   std::istream &s, CONTAINER &vec,
   const std::string &label, const std::string &context
) {
   using elem = typename CONTAINER::value_type;

   // read number of elements
   std::size_t nelem;
   if (!(s >> nelem)) {
      std::ostringstream oss;
      oss << "Could not read number of " << label << " values";
      error(oss,context);
      return false;
   }

   // reserve space
   vec.reserve(nelem);

   // read elements
   const loop e(nelem);
   while (e()) {
      elem element;
      if (!(s >> element)) {
         std::ostringstream oss;
         oss << "Could not read " << label << '[' << std::size_t(e) << ']';
         error(oss,context);
         return false;
      }
      vec.push_back(element);
   }

   return true;
}



// element_container_write
template<class CONTAINER>
bool element_container_write(
   std::ostream &s, const CONTAINER &vec,
   const std::string &label, const std::string &context
) {
   // write number of elements
   const std::size_t nelem = vec.size();
   if (!(s << nelem << '\n')) {
      std::ostringstream oss;
      oss << "Could not write number of " << label << " values";
      error(oss,context);
      return false;
   }

   // write elements
   const loop e(nelem);
   while (e()) {
      std::ostringstream buf;
      buf << vec[e];
      if (!buf || (buf.str() != "" && !(s << "   " << buf.str() << '\n'))) {
         std::ostringstream oss;
         oss << "Could not write " << label << '[' << std::size_t(e) << ']';
         error(oss,context);
         return false;
      }
   }

   return true;
}

}  // internal
}  // metamesh



// =============================================================================
// read_nefc
// =============================================================================

namespace metamesh {
namespace internal {

// 0-form
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool read_nefc(
   std::istream &s,
   mesh<node_t,edge_t,face_t,cell_t,base_t,0> &obj,
   const std::string &context
) {
   return
      element_container_read(s, obj.node, "node", context);
}


// 1-form
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool read_nefc(
   std::istream &s,
   mesh<node_t,edge_t,face_t,cell_t,base_t,1> &obj,
   const std::string &context
) {
   return
      element_container_read(s, obj.node, "node", context) &&
      element_container_read(s, obj.edge, "edge", context);
}


// 2-form
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool read_nefc(
   std::istream &s,
   mesh<node_t,edge_t,face_t,cell_t,base_t,2> &obj,
   const std::string &context
) {
   return
      element_container_read(s, obj.node, "node", context) &&
      element_container_read(s, obj.edge, "edge", context) &&
      element_container_read(s, obj.face, "face", context);
}


// 3-form
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool read_nefc(
   std::istream &s,
   mesh<node_t,edge_t,face_t,cell_t,base_t,3> &obj,
   const std::string &context
) {
   return
      element_container_read(s, obj.node, "node", context) &&
      element_container_read(s, obj.edge, "edge", context) &&
      element_container_read(s, obj.face, "face", context) &&
      element_container_read(s, obj.cell, "cell", context);
}

}  // internal
}  // metamesh



// =============================================================================
// write_nefc
// =============================================================================

namespace metamesh {
namespace internal {

// 0-form
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool write_nefc(
   std::ostream &s,
   const mesh<node_t,edge_t,face_t,cell_t,base_t,0> &obj,
   const std::string &context
) {
   return
      element_container_write(s, obj.node, "node", context);
}


// 1-form
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool write_nefc(
   std::ostream &s,
   const mesh<node_t,edge_t,face_t,cell_t,base_t,1> &obj,
   const std::string &context
) {
   return
      element_container_write(s, obj.node, "node", context) &&
      element_container_write(s, obj.edge, "edge", context);
}


// 2-form
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool write_nefc(
   std::ostream &s,
   const mesh<node_t,edge_t,face_t,cell_t,base_t,2> &obj,
   const std::string &context
) {
   return
      element_container_write(s, obj.node, "node", context) &&
      element_container_write(s, obj.edge, "edge", context) &&
      element_container_write(s, obj.face, "face", context);
}


// 3-form
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool write_nefc(
   std::ostream &s,
   const mesh<node_t,edge_t,face_t,cell_t,base_t,3> &obj,
   const std::string &context
) {
   return
      element_container_write(s, obj.node, "node", context) &&
      element_container_write(s, obj.edge, "edge", context) &&
      element_container_write(s, obj.face, "face", context) &&
      element_container_write(s, obj.cell, "cell", context);
}

}  // internal
}  // metamesh

#endif
