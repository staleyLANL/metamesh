/* -*- C++ -*- */

#ifndef METAMESH_MESH
#define METAMESH_MESH

/*
   This file provides the mesh class and related functionality. The following
   specializations are made:

      0-form mesh, available in 0d, 1d, 2d, 3d:
      -----------

         class mesh<
            node<nterms,nbase>,
            base,
            default_base_t,
            default_base_t,
            default_base_t,
            0
         >

      1-form mesh, available in 1d, 2d, 3d:
      -----------

         class mesh<
            node<nterms,nbase>,
            edge<eterms,ebase>,
            base,
            default_base_t,
            default_base_t,
            1
         >

      2-form mesh, available in 2d, 3d:
      -----------

         class mesh<
            node<nterms,nbase>,
            edge<eterms,ebase>,
            face<fterms,fbase>,
            base,
            default_base_t,
            2
         >

      3-form mesh, available in 3d:
      -----------

         class mesh<
            node<nterms,nbase>,
            edge<eterms,ebase>,
            face<fterms,fbase>,
            cell<cterms,cbase>,
            base,
            3
         >

   Together, these cover what we regard as the sensible mesh variants.
*/



// =============================================================================
// Miscellaneous:
//    tclass
//    if_true
//    element_size
//    ge0
// Helper constructs
// =============================================================================

namespace metamesh {
namespace internal {

// tclass
// Helper class; type wrapper
template<class> class tclass { };

// if_true
// Compile-time extraction of ::type succeeds iff <true>
template<bool b, class T>
class if_true { public: using type = T; };

template<class T>
class if_true<false,T> { };



// element_size
// Compile-time extraction of .size() of a particular mesh element
template<class nterms, class nbase, class MESH>
inline std::size_t
element_size(const tclass<node<nterms,nbase>>, const MESH &mesh)
   { return mesh.node.size(); }

template<class eterms, class ebase, class MESH>
inline std::size_t
element_size(const tclass<edge<eterms,ebase>>, const MESH &mesh)
   { return mesh.edge.size(); }

template<class fterms, class fbase, class MESH>
inline std::size_t
element_size(const tclass<face<fterms,fbase>>, const MESH &mesh)
   { return mesh.face.size(); }

template<class cterms, class cbase, class MESH>
inline std::size_t
element_size(const tclass<cell<cterms,cbase>>, const MESH &mesh)
   { return mesh.cell.size(); }



// ge0
// SFINAE scheme to inhibit compiler warnings from checking
// that an unsigned type is non-negative.

template<class itype>
inline typename if_true<
   std::numeric_limits<itype>::is_signed ||
  !std::numeric_limits<itype>::is_integer,
   bool  // result type
>::type ge0(const itype &i)
{
   // signed integer or non-integer (which presumably is signed)
   return !(i < 0);
}

template<class itype>
inline typename if_true<
  !std::numeric_limits<itype>::is_signed &&
   std::numeric_limits<itype>::is_integer,
   bool  // result type
>::type ge0(const itype &)
{
   // unsigned integer; >= 0 is necessarily true
   return true;
}

}  // internal
}  // metamesh



// =============================================================================
// same_nef
// The "nef" ending of this name is an abbreviation for node, edge, and face.
// The class assists with certain compile-time consistency checking regarding
// the template parameters of a mesh. For example, the node type on which the
// edge type of a mesh is based (via the edge's "terms") should be identical
// to the node type of the mesh.
// =============================================================================

namespace metamesh {
namespace internal {

// ------------------------
// Default
// ------------------------

template<
   class basis_t,       // basis that should be node_t, edge_t, or face_t
   class node_t,        // node type of a mesh
   class edge_t = stub, // edge type, if any, of a mesh
   class face_t = stub  // face type, if any, of a mesh
>
class same_nef {
   // nothing
};



// ------------------------
// 1-form
// ------------------------

// basis matches node
template<
   class nterms, class nbase
>
class same_nef<
   node<nterms,nbase>,
   node<nterms,nbase>,
   stub,
   stub
> {
   public: using type = node<nterms,nbase>;
};



// ------------------------
// 2-form
// ------------------------

// basis matches node
template<
   class nterms, class nbase,
   class eterms, class ebase
>
class same_nef<
   node<nterms,nbase>,
   node<nterms,nbase>,
   edge<eterms,ebase>,
   stub
> {
   public: using type = node<nterms,nbase>;
};

// basis matches edge
template<
   class nterms, class nbase,
   class eterms, class ebase
>
class same_nef<
   edge<eterms,ebase>,
   node<nterms,nbase>,
   edge<eterms,ebase>,
   stub
> {
   public: using type = edge<eterms,ebase>;
};



// ------------------------
// 3-form
// ------------------------

// basis matches node
template<
   class nterms, class nbase,
   class eterms, class ebase,
   class fterms, class fbase
>
class same_nef<
   node<nterms,nbase>,
   node<nterms,nbase>,
   edge<eterms,ebase>,
   face<fterms,fbase>
> {
   public: using type = node<nterms,nbase>;
};

// basis matches edge
template<
   class nterms, class nbase,
   class eterms, class ebase,
   class fterms, class fbase
>
class same_nef<
   edge<eterms,ebase>,
   node<nterms,nbase>,
   edge<eterms,ebase>,
   face<fterms,fbase>
> {
   public: using type = edge<eterms,ebase>;
};

// basis matches face
template<
   class nterms, class nbase,
   class eterms, class ebase,
   class fterms, class fbase
>
class same_nef<
   face<fterms,fbase>,
   node<nterms,nbase>,
   edge<eterms,ebase>,
   face<fterms,fbase>
> {
   public: using type = face<fterms,fbase>;
};

}  // internal
}  // metamesh



// =============================================================================
// is_node
// is_edge
// is_face
// is_cell
// Helper classes
// =============================================================================

// Compile-time extraction of ::value gives 1 if the template parameter
// is of the appropriate element type, 0 otherwise

namespace metamesh {
namespace internal {

   // is_node
   template<class T>
   class is_node                   { public: static const bool value = 0; };
   template<class terms, class base>
   class is_node<node<terms,base>> { public: static const bool value = 1; };

   // is_edge
   template<class T>
   class is_edge                   { public: static const bool value = 0; };
   template<class terms, class base>
   class is_edge<edge<terms,base>> { public: static const bool value = 1; };

   // is_face
   template<class T>
   class is_face                   { public: static const bool value = 0; };
   template<class terms, class base>
   class is_face<face<terms,base>> { public: static const bool value = 1; };

   // is_cell
   template<class T>
   class is_cell                   { public: static const bool value = 0; };
   template<class terms, class base>
   class is_cell<cell<terms,base>> { public: static const bool value = 1; };

}  // internal
}  // metamesh



// =============================================================================
// mesh
// Default
// =============================================================================

namespace metamesh {

template<
   // Node, edge, face, cell
   class node_t,
   class edge_t = default_base_t,
   class face_t = default_base_t,
   class cell_t = default_base_t,

   // Base
   class base_t = default_base_t,

   // Form, not dimension. For example, a Mobius strip is a 2-form
   // in three dimensions. Dimension will come from the node's terms.
   std::size_t form =
      std::size_t(internal::is_edge<edge_t>::value)  // w/edges; at least 1-form
    + std::size_t(internal::is_face<face_t>::value)  // w/faces; at least 2-form
    + std::size_t(internal::is_cell<cell_t>::value)  // w/cells; 3-form
>
class mesh { };

}  // metamesh



// Macro for building certain functions inside upcoming mesh specializations:
// label, push, elements, const elements, operator(), const operator()

#define metamesh_mesh_functions(elem_t,elem,n)\
   static inline const char *label(const component<n>)\
      { return elem_t::label(); }\
   \
   inline elem_t &push(const elem_t &from)\
      { return elem.push_back(from), elem.back(); }\
   \
   inline       std::vector<elem_t> &elements(const component<n>)\
      { return elem; }\
   inline const std::vector<elem_t> &elements(const component<n>) const\
      { return elem; }\
   \
   template<class index_t>\
   inline elem_t       &operator()(const index_to<elem_t,index_t> i)\
   {\
      metamesh_assert(internal::ge0(index_t(i)) && index_t(i) < elem.size());\
      return elem[index_t(i)];\
   }\
   template<class index_t>\
   inline const elem_t &operator()(const index_to<elem_t,index_t> i) const\
   {\
      metamesh_assert(internal::ge0(index_t(i)) && index_t(i) < elem.size());\
      return elem[index_t(i)];\
   }



// =============================================================================
// 0-form mesh
//    node
// =============================================================================

namespace metamesh {

template<
   class nterms, class nbase, class _base
>
class mesh<
   // node
   node<nterms,nbase>,

   // mesh base
  _base,
   default_base_t,
   default_base_t,
   default_base_t,

   0  // form == 0, and must be <= dimension...
> : public internal::if_true<0 <= node<nterms,nbase>::dimension, _base>::type
{
public:

   // types
   using node_t  =  metamesh::node<nterms,nbase>; using zone_t = node_t;
   using base_t  = _base;
   using value_t =  typename node_t::value_t;

   // form, dimension
   static const std::size_t form = 0;
   static const std::size_t dimension = node_t::dimension;

   // label
   static inline const char *label(void) { return "mesh"; }

   // elements
   std::vector<node_t> node, &zone;


   // ------------------------
   // Constructor, assignment
   // ------------------------

   // mesh()
   // mesh(base)
   inline explicit mesh(const base_t &base = base_t()) :
      base_t(base), zone(node)
   {
      #ifdef METAMESH_DEBUG
      std::cout << "0-form mesh" << std::endl;
      #endif
   }

   // assignment to base
   inline mesh &operator=(const base_t &from) { return base() = from, *this; }

   // copy constructor
   inline mesh(const mesh &from) :
      base_t(from.base()),
      node(from.node), zone(node)
   { }

   // copy assignment
   inline mesh &operator=(const mesh &from)
   {
      this->base_t::operator=(from.base());
      node = from.node;
      return *this;
   }


   // ------------------------
   // Miscellaneous
   // ------------------------

   // base()
   inline       base_t &base(void)       { return *this; }
   inline const base_t &base(void) const { return *this; }

   // clear()
   inline void clear(void)
   {
      node.clear();
   }


   // ------------------------
   // Generic access
   // ------------------------

   metamesh_mesh_functions(node_t, node, 0)


   // ------------------------
   // check
   // ------------------------

   inline diagnostic_t check(
      const std::string &context = "",
      const std::size_t nstart = 0  // [index] at which to begin node checks
      // qqq where would a non-default nstart be used?
   ) const {
      // node
      const diagnostic_t ncheck = internal::check_elements(
         node, nstart, "node", context
      );

      // base
      const diagnostic_t base_check = base().check(internal::new_context(
         "Detected during mesh.check's examination of base", context
      ));

      return metamesh::min(ncheck, base_check);
   }
};



// ------------------------
// form, dimension
// ------------------------

// form
template<
   class nterms, class nbase, class base_t>
const std::size_t mesh<
   node<nterms,nbase>, base_t,
   default_base_t, default_base_t, default_base_t, 0
>::form;

// dimension
template<
   class nterms, class nbase, class base_t>
const std::size_t mesh<
   node<nterms,nbase>, base_t,
   default_base_t, default_base_t, default_base_t, 0
>::dimension;

}  // metamesh



// =============================================================================
// 1-form mesh
//    node
//    edge
// =============================================================================

namespace metamesh {

template<
   class nterms, class nbase,
   class eterms, class ebase, class _base
>
class mesh<
   // node, edge
   node<nterms,nbase>,
   edge<eterms,ebase>,

   // mesh base
  _base,
   default_base_t,
   default_base_t,

   1  // form == 1, and must be <= dimension...
> : public internal::if_true<1 <= node<nterms,nbase>::dimension, _base>::type
{

   // ensure that edge basis is node type
   using edge_basis_must_equal_node = typename internal::same_nef<
      typename eterms::basis_t,
      metamesh::node<nterms,nbase>
   >::type;

public:

   // types
   using node_t  =  metamesh::node<nterms,nbase>;
   using edge_t  =  metamesh::edge<eterms,ebase>; using zone_t = edge_t;
   using base_t  = _base;
   using value_t =  typename node_t::value_t;

   // form, dimension
   static const std::size_t form = 1;
   static const std::size_t dimension = node_t::dimension;

   // label
   static inline const char *label(void) { return "mesh"; }

   // elements
   std::vector<node_t> node;
   std::vector<edge_t> edge, &zone;


   // ------------------------
   // Constructor, assignment
   // ------------------------

   // mesh()
   // mesh(base)
   inline explicit mesh(const base_t &base = base_t()) :
      base_t(base), zone(edge)
   {
      #ifdef METAMESH_DEBUG
      std::cout << "1-form mesh" << std::endl;
      #endif
   }

   // assignment to base
   inline mesh &operator=(const base_t &from) { return base() = from, *this; }

   // copy constructor
   inline mesh(const mesh &from) :
      base_t(from.base()),
      node(from.node),
      edge(from.edge), zone(edge)
   { }

   // copy assignment
   inline mesh &operator=(const mesh &from)
   {
      this->base_t::operator=(from.base());
      node = from.node;
      edge = from.edge;
      return *this;
   }


   // ------------------------
   // Miscellaneous
   // ------------------------

   // base()
   inline       base_t &base(void)       { return *this; }
   inline const base_t &base(void) const { return *this; }

   // clear()
   inline void clear(void)
   {
      node.clear();
      edge.clear();
   }


   // ------------------------
   // Generic access
   // ------------------------

   metamesh_mesh_functions(node_t, node, 0)
   metamesh_mesh_functions(edge_t, edge, 1)


   // ------------------------
   // check
   // ------------------------

   inline diagnostic_t check(
      const std::string &context = "",
      const std::size_t nstart = 0, // [index] at which to begin node checks
      const std::size_t estart = 0  // [index] at which to begin edge checks
   ) const {
      // node, edge
      const diagnostic_t ncheck = internal::check_elements(
         node, nstart, "node", context
      );
      const diagnostic_t echeck = internal::check_elements(
         edge, estart, "edge", context,
         internal::element_size(
            internal::tclass<typename edge_t::basis_t>(), *this)
      );

      // base
      const diagnostic_t base_check = base().check(internal::new_context(
         "Detected during mesh.check's examination of base", context
      ));

      return metamesh::min(ncheck,echeck, base_check);
   }
};



// ------------------------
// form, dimension
// ------------------------

// form
template<
   class nterms, class nbase,
   class eterms, class ebase, class base_t>
const std::size_t mesh<
   node<nterms,nbase>,
   edge<eterms,ebase>, base_t,
   default_base_t, default_base_t, 1
>::form;

// dimension
template<
   class nterms, class nbase,
   class eterms, class ebase, class base_t>
const std::size_t mesh<
   node<nterms,nbase>,
   edge<eterms,ebase>, base_t,
   default_base_t, default_base_t, 1
>::dimension;

}  // metamesh



// =============================================================================
// 2-form mesh
//    node
//    edge
//    face
// =============================================================================

namespace metamesh {

template<
   class nterms, class nbase,
   class eterms, class ebase,
   class fterms, class fbase, class _base
>
class mesh<
   // node, edge, face
   node<nterms,nbase>,
   edge<eterms,ebase>,
   face<fterms,fbase>,

   // mesh base
  _base,
   default_base_t,

   2  // form == 2, and must be <= dimension...
> : public internal::if_true<2 <= node<nterms,nbase>::dimension, _base>::type
{

   // ensure that edge basis is node type
   using edge_basis_must_equal_node = typename internal::same_nef<
      typename eterms::basis_t,
      metamesh::node<nterms,nbase>
   >::type;

   // ensure that face basis is edge or node type
   using face_basis_must_equal_node_or_edge = typename internal::same_nef<
      typename fterms::basis_t,
      metamesh::node<nterms,nbase>,
      metamesh::edge<eterms,ebase>
   >::type;

public:

   // types
   using node_t  =  metamesh::node<nterms,nbase>;
   using edge_t  =  metamesh::edge<eterms,ebase>;
   using face_t  =  metamesh::face<fterms,fbase>; using zone_t = face_t;
   using base_t  = _base;
   using value_t =  typename node_t::value_t;

   // form, dimension
   static const std::size_t form = 2;
   static const std::size_t dimension = node_t::dimension;

   // label
   static inline const char *label(void) { return "mesh"; }

   // elements
   std::vector<node_t> node;
   std::vector<edge_t> edge;
   std::vector<face_t> face, &zone;


   // ------------------------
   // Constructor, assignment
   // ------------------------

   // mesh()
   // mesh(base)
   inline explicit mesh(const base_t &base = base_t()) :
      base_t(base), zone(face)
   {
      #ifdef METAMESH_DEBUG
      std::cout << "2-form mesh" << std::endl;
      #endif
   }

   // assignment to base
   inline mesh &operator=(const base_t &from) { return base() = from, *this; }

   // copy constructor
   inline mesh(const mesh &from) :
      base_t(from.base()),
      node(from.node),
      edge(from.edge),
      face(from.face), zone(face)
   { }

   // copy assignment
   inline mesh &operator=(const mesh &from)
   {
      this->base_t::operator=(from.base());
      node = from.node;
      edge = from.edge;
      face = from.face;
      return *this;
   }


   // ------------------------
   // Miscellaneous
   // ------------------------

   // base()
   inline       base_t &base(void)       { return *this; }
   inline const base_t &base(void) const { return *this; }

   // clear()
   inline void clear(void)
   {
      node.clear();
      edge.clear();
      face.clear();
   }


   // ------------------------
   // Generic access
   // ------------------------

   metamesh_mesh_functions(node_t, node, 0)
   metamesh_mesh_functions(edge_t, edge, 1)
   metamesh_mesh_functions(face_t, face, 2)


   // ------------------------
   // check
   // ------------------------

   inline diagnostic_t check(
      const std::string &context = "",
      const std::size_t nstart = 0, // [index] at which to begin node checks
      const std::size_t estart = 0, // [index] at which to begin edge checks
      const std::size_t fstart = 0  // [index] at which to begin face checks
   ) const {
      // node, edge, face
      const diagnostic_t ncheck = internal::check_elements(
         node, nstart, "node", context
      );
      const diagnostic_t echeck = internal::check_elements(
         edge, estart, "edge", context,
         internal::element_size(
            internal::tclass<typename edge_t::basis_t>(), *this)
      );
      const diagnostic_t fcheck = internal::check_elements(
         face, fstart, "face", context,
         internal::element_size(
            internal::tclass<typename face_t::basis_t>(), *this)
      );

      // base
      const diagnostic_t base_check = base().check(internal::new_context(
         "Detected during mesh.check's examination of base", context
      ));

      return metamesh::min(ncheck,echeck,fcheck, base_check);
   }
};



// ------------------------
// form, dimension
// ------------------------

// form
template<
   class nterms, class nbase,
   class eterms, class ebase,
   class fterms, class fbase, class base_t>
const std::size_t mesh<
   node<nterms,nbase>,
   edge<eterms,ebase>,
   face<fterms,fbase>, base_t,
   default_base_t, 2
>::form;

// dimension
template<
   class nterms, class nbase,
   class eterms, class ebase,
   class fterms, class fbase, class base_t>
const std::size_t mesh<
   node<nterms,nbase>,
   edge<eterms,ebase>,
   face<fterms,fbase>, base_t,
   default_base_t, 2
>::dimension;

}  // metamesh



// =============================================================================
// 3-form mesh
//    node
//    edge
//    face
//    cell
// =============================================================================

namespace metamesh {

template<
   class nterms, class nbase,
   class eterms, class ebase,
   class fterms, class fbase,
   class cterms, class cbase, class _base
>
class mesh<
   // node, edge, face, cell
   node<nterms,nbase>,
   edge<eterms,ebase>,
   face<fterms,fbase>,
   cell<cterms,cbase>,

   // mesh base
  _base,

   3  // form == 3, and must be <= dimension...
> : public internal::if_true<3 <= node<nterms,nbase>::dimension, _base>::type
{

   // ensure that edge basis is node type
   using edge_basis_must_equal_node =
   typename internal::same_nef<
      typename eterms::basis_t,
      metamesh::node<nterms,nbase>
   >::type;

   // ensure that face basis is edge or node type
   using face_basis_must_equal_node_or_edge =
   typename internal::same_nef<
      typename fterms::basis_t,
      metamesh::node<nterms,nbase>,
      metamesh::edge<eterms,ebase>
   >::type;

   // ensure that cell basis is face, edge or node type
   using cell_basis_must_equal_node_or_edge_or_face =
   typename internal::same_nef<
      typename cterms::basis_t,
      metamesh::node<nterms,nbase>,
      metamesh::edge<eterms,ebase>,
      metamesh::face<fterms,fbase>
   >::type;

public:

   // types
   using node_t  =  metamesh::node<nterms,nbase>;
   using edge_t  =  metamesh::edge<eterms,ebase>;
   using face_t  =  metamesh::face<fterms,fbase>;
   using cell_t  =  metamesh::cell<cterms,cbase>; using zone_t = cell_t;
   using base_t  = _base;
   using value_t =  typename node_t::value_t;

   // form, dimension
   static const std::size_t form = 3;
   static const std::size_t dimension = node_t::dimension;

   // label
   static inline const char *label(void) { return "mesh"; }

   // elements
   std::vector<node_t> node;
   std::vector<edge_t> edge;
   std::vector<face_t> face;
   std::vector<cell_t> cell, &zone;


   // ------------------------
   // Constructor, assignment
   // ------------------------

   // mesh()
   // mesh(base)
   inline explicit mesh(const base_t &base = base_t()) :
      base_t(base), zone(cell)
   {
      #ifdef METAMESH_DEBUG
      std::cout << "3-form mesh" << std::endl;
      #endif
   }

   // assignment to base
   inline mesh &operator=(const base_t &from) { return base() = from, *this; }

   // copy constructor
   inline mesh(const mesh &from) :
      base_t(from.base()),
      node(from.node),
      edge(from.edge),
      face(from.face),
      cell(from.cell), zone(cell)
   { }

   // copy assignment
   inline mesh &operator=(const mesh &from)
   {
      this->base_t::operator=(from.base());
      node = from.node;
      edge = from.edge;
      face = from.face;
      cell = from.cell;
      return *this;
   }


   // ------------------------
   // Miscellaneous
   // ------------------------

   // base()
   inline       base_t &base(void)       { return *this; }
   inline const base_t &base(void) const { return *this; }

   // clear()
   inline void clear(void)
   {
      node.clear();
      edge.clear();
      face.clear();
      cell.clear();
   }


   // ------------------------
   // Generic access
   // ------------------------

   metamesh_mesh_functions(node_t, node, 0)
   metamesh_mesh_functions(edge_t, edge, 1)
   metamesh_mesh_functions(face_t, face, 2)
   metamesh_mesh_functions(cell_t, cell, 3)


   // ------------------------
   // check
   // ------------------------

   inline diagnostic_t check(
      const std::string &context = "",
      const std::size_t nstart = 0, // [index] at which to begin node checks
      const std::size_t estart = 0, // [index] at which to begin edge checks
      const std::size_t fstart = 0, // [index] at which to begin face checks
      const std::size_t cstart = 0  // [index] at which to begin cell checks
   ) const {
      // node, edge, face, cell
      const diagnostic_t ncheck = internal::check_elements(
         node, nstart, "node", context
      );
      const diagnostic_t echeck = internal::check_elements(
         edge, estart, "edge", context,
         internal::element_size(
            internal::tclass<typename edge_t::basis_t>(), *this)
      );
      const diagnostic_t fcheck = internal::check_elements(
         face, fstart, "face", context,
         internal::element_size(
            internal::tclass<typename face_t::basis_t>(), *this)
      );
      const diagnostic_t ccheck = internal::check_elements(
         cell, cstart, "cell", context,
         internal::element_size(
            internal::tclass<typename cell_t::basis_t>(), *this)
      );

      // base
      const diagnostic_t base_check = base().check(internal::new_context(
         "Detected during mesh.check's examination of base", context
      ));

      return metamesh::min(ncheck,echeck,fcheck,ccheck, base_check);
   }
};



// ------------------------
// form, dimension
// ------------------------

// form
template<
   class nterms, class nbase,
   class eterms, class ebase,
   class fterms, class fbase,
   class cterms, class cbase, class base_t>
const std::size_t mesh<
   node<nterms,nbase>,
   edge<eterms,ebase>,
   face<fterms,fbase>,
   cell<cterms,cbase>, base_t,
   3
>::form;

// dimension
template<
   class nterms, class nbase,
   class eterms, class ebase,
   class fterms, class fbase,
   class cterms, class cbase, class base_t>
const std::size_t mesh<
   node<nterms,nbase>,
   edge<eterms,ebase>,
   face<fterms,fbase>,
   cell<cterms,cbase>, base_t,
   3
>::dimension;

}  // metamesh



// =============================================================================
// i/o for all mesh variants
// =============================================================================

namespace metamesh {

// istream >> mesh
template<class ntype, class etype, class ftype, class ctype, class base>
std::istream &operator>>(
   std::istream &s,
   metamesh::mesh<ntype,etype,ftype,ctype,base> &obj
) {
   const char *const context = "Detected during istream >> mesh";

   // clear
   obj.clear();

   // read nodes, edges, faces, and cells, as appropriate
   if (!internal::read_nefc(s, obj, context))
      return obj.clear(), s;

   // read base
   if (!(s >> obj.base())) {
      metamesh::error("Could not read base", context);
      return obj.clear(), s;
   }

   // check
   if (obj.check("Detected in mesh.check call after istream >> mesh") ==
       metamesh::diagnostic_error)
      obj.clear();

   // done
   return s;
}



// ostream << mesh
template<class ntype, class etype, class ftype, class ctype, class base>
std::ostream &operator<<(
   std::ostream &s,
   const metamesh::mesh<ntype,etype,ftype,ctype,base> &obj
) {
   const char *const context = "Detected during ostream << mesh";

   // check
   if (obj.check("Detected in mesh.check call before ostream << mesh") ==
       metamesh::diagnostic_error)
      return s;

   // write nodes, edges, faces, and cells, as appropriate
   if (!internal::write_nefc(s, obj, context))
      return s;

   // write base
   std::ostringstream buf;
   buf << obj.base();
   if (!buf || (buf.str() != "" && !(s << buf.str())))
      metamesh::error("Could not write base", context);

   // done
   return s;
}

}  // metamesh

#undef metamesh_mesh_functions



// =============================================================================
// operator,
// =============================================================================

// non-const
template<
   class ntype, class etype, class ftype, class ctype, class base,
   std::size_t form,
   class nefc, class index_t>
inline nefc &operator,(
   metamesh::mesh<ntype,etype,ftype,ctype,base,form> &mesh,
   const metamesh::index_to<nefc,index_t> i
) {
   return mesh(i);
}

// const
template<
   class ntype, class etype, class ftype, class ctype, class base,
   std::size_t form,
   class nefc, class index_t>
inline const nefc &operator,(
   const metamesh::mesh<ntype,etype,ftype,ctype,base,form> &mesh,
   const metamesh::index_to<nefc,index_t> i
) {
   return mesh(i);
}

#endif
