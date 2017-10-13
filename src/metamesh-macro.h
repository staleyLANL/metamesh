/* -*- C++ -*- */

#ifndef METAMESH_MACRO
#define METAMESH_MACRO

/*
   This file provides some macros that should help users write callbacks within
   their extrusion-algorithm function objects.

   For each macro, IMESH and OMESH are, respectively, the input and output mesh
   types involved in the extrusion. Nearly any mesh type will contain commas,
   in order to separate template parameters. Therefore, in order for the macros
   to work correctly, you should probably make alias declarations (or typedefs)
   for your mesh types, and use those - not comma'd mesh names! - in the macros.

   Each macro that makes a function signature is accompanied by a macro ending
   in _param. The _param macro can be used in the function's body, in order to
   ensure that each parameter is referenced (even if only via a cast to void).
   This may prevent "unused parameter" warnings from some compilers. One can
   normally avoid such warnings by excluding the names of placeholder parameters
   that are otherwise unused. However, because that isn't possible when you use
   these macros to make function signatures, the _param macro can be useful for
   suppressing the warning.

   Example macro usage:

      class your_function_object {
      public:
         inline metamesh_macro_path(input_mesh_t, output_mesh_t) const
         {
            metamesh_macro_path_param;  // may suppress warnings
            // YOUR CODE HERE!
         }
      };

   The _param macros are designed so that a ';' can (and should!) be placed at
   the end. The semicolon may prevent an auto-formatting editor from going nuts.
*/



// =============================================================================
// if_extrude_compatible
// SFINAE scheme to ensure compatible input and output meshes for extrusion.
// =============================================================================

namespace metamesh {
namespace internal {

// default
template<class IMESH, class OMESH, class T>
class if_extrude_compatible { };

// compatible
template<
   class inode, class iedge, class iface, class icell, class ibase,
   std::size_t iform,
   class onode, class oedge, class oface, class ocell, class obase,
   class T
>
class if_extrude_compatible<
   mesh<inode,iedge,iface,icell,ibase,iform>,
   mesh<onode,oedge,oface,ocell,obase,iform+1>,
   T
> {
public:
   using type = T;
};

}  // internal
}  // metamesh



// =============================================================================
// path (extrusion path)
// more (continuation condition)
// =============================================================================

// ------------------------
// path
// ------------------------

// input : imesh, omesh, layer, n, inode
// output: onode
// return: void
#define metamesh_macro_path(IMESH,OMESH)\
   typename metamesh::internal::if_extrude_compatible<IMESH,OMESH,void>::type\
   path(\
      const IMESH &imesh,\
      const OMESH &omesh,\
      const std::size_t layer,\
      const std::size_t n,\
      const typename IMESH::node_t &inode,\
            typename OMESH::node_t &onode\
   )

#define metamesh_macro_path_param\
   (void)imesh; (void)omesh;\
   (void)layer; (void)n;\
   (void)inode; (void)onode



// ------------------------
// more
// ------------------------

// input : imesh, omesh, layer
// output: none
// return: bool
#define metamesh_macro_more(IMESH,OMESH)\
   typename metamesh::internal::if_extrude_compatible<IMESH,OMESH,bool>::type\
   more(\
      const IMESH &imesh,\
      const OMESH &omesh,\
      const std::size_t layer\
   )

#define metamesh_macro_more_param\
   (void)imesh; (void)omesh;\
   (void)layer



// =============================================================================
// masking
// =============================================================================

// ------------------------
// node_on
// ------------------------

// input : imesh, omesh, layer, n, inode, onode
// output: none
// return: bool
#define metamesh_macro_node_on(IMESH,OMESH)\
   typename metamesh::internal::if_extrude_compatible<IMESH,OMESH,bool>::type\
   node_on(\
      const IMESH &imesh,\
      const OMESH &omesh,\
      const std::size_t layer,\
      const std::size_t n,\
      const typename IMESH::node_t &inode,\
      const std::vector<typename OMESH::node_t> &onodes\
   )

#define metamesh_macro_node_on_param\
   (void)imesh; (void)omesh;\
   (void)layer; (void)n;\
   (void)inode; (void)onodes



// ------------------------
// edge_on
// ------------------------

// input : imesh, omesh, layer, e, iedge, onodes
// output: none
// return: bool
#define metamesh_macro_edge_on(IMESH,OMESH)\
   typename metamesh::internal::if_extrude_compatible<IMESH,OMESH,bool>::type\
   edge_on(\
      const IMESH &imesh,\
      const OMESH &omesh,\
      const std::size_t layer,\
      const std::size_t e,\
      const typename IMESH::edge_t &iedge,\
      const std::vector<typename OMESH::node_t> &onodes\
   )

#define metamesh_macro_edge_on_param\
   (void)imesh; (void)omesh;\
   (void)layer; (void)e;\
   (void)iedge; (void)onodes



// ------------------------
// face_on
// ------------------------

// input : imesh, omesh, layer, f, iface, onodes
// output: none
// return: bool
#define metamesh_macro_face_on(IMESH,OMESH)\
   typename metamesh::internal::if_extrude_compatible<IMESH,OMESH,bool>::type\
   face_on(\
      const IMESH &imesh,\
      const OMESH &omesh,\
      const std::size_t layer,\
      const std::size_t f,\
      const typename IMESH::face_t &iface,\
      const std::vector<typename OMESH::node_t> &onodes\
   )

#define metamesh_macro_face_on_param\
   (void)imesh; (void)omesh;\
   (void)layer; (void)f;\
   (void)iface; (void)onodes



// =============================================================================
// action
// =============================================================================

// ------------------------
// action
// ------------------------

// input : imesh, omesh, layer
// output: none
// return: void
#define metamesh_macro_action(IMESH,OMESH)\
   typename metamesh::internal::if_extrude_compatible<IMESH,OMESH,void>::type\
   action(\
      const IMESH &imesh,\
      const OMESH &omesh,\
      const std::size_t layer\
   )

#define metamesh_macro_action_param\
   (void)imesh; (void)omesh;\
   (void)layer



// =============================================================================
// base propagation
// =============================================================================

// ------------------------
// node2node
// ------------------------

// input : imesh, omesh, layer, n, inode
// output: onode
// return: void
#define metamesh_macro_node2node(IMESH,OMESH)\
   typename metamesh::internal::if_extrude_compatible<IMESH,OMESH,void>::type\
   node2node(\
      const IMESH &imesh,\
      const OMESH &omesh,\
      const std::size_t layer,\
      const std::size_t n,\
      const typename IMESH::node_t &inode,\
            typename OMESH::node_t &onode\
   )

#define metamesh_macro_node2node_param\
   (void)imesh; (void)omesh;\
   (void)layer; (void)n;\
   (void)inode; (void)onode



// ------------------------
// node2edge
// ------------------------

// input : imesh, omesh, layer, n, inode
// output: oedge
// return: void
#define metamesh_macro_node2edge(IMESH,OMESH)\
   typename metamesh::internal::if_extrude_compatible<IMESH,OMESH,void>::type\
   node2edge(\
      const IMESH &imesh,\
      const OMESH &omesh,\
      const std::size_t layer,\
      const std::size_t n,\
      const typename IMESH::node_t &inode,\
            typename OMESH::edge_t &oedge\
   )

#define metamesh_macro_node2edge_param\
   (void)imesh; (void)omesh;\
   (void)layer; (void)n;\
   (void)inode; (void)oedge



// ------------------------
// edge2edge
// ------------------------

// input : imesh, omesh, layer, e, iedge
// output: oedge
// return: void
#define metamesh_macro_edge2edge(IMESH,OMESH)\
   typename metamesh::internal::if_extrude_compatible<IMESH,OMESH,void>::type\
   edge2edge(\
      const IMESH &imesh,\
      const OMESH &omesh,\
      const std::size_t layer,\
      const std::size_t e,\
      const typename IMESH::edge_t &iedge,\
            typename OMESH::edge_t &oedge\
   )

#define metamesh_macro_edge2edge_param\
   (void)imesh; (void)omesh;\
   (void)layer; (void)e;\
   (void)iedge; (void)oedge



// ------------------------
// edge2face
// ------------------------

// input : imesh, omesh, layer, e, iedge
// output: oface
// return: void
#define metamesh_macro_edge2face(IMESH,OMESH)\
   typename metamesh::internal::if_extrude_compatible<IMESH,OMESH,void>::type\
   edge2face(\
      const IMESH &imesh,\
      const OMESH &omesh,\
      const std::size_t layer,\
      const std::size_t e,\
      const typename IMESH::edge_t &iedge,\
            typename OMESH::face_t &oface\
   )

#define metamesh_macro_edge2face_param\
   (void)imesh; (void)omesh;\
   (void)layer; (void)e;\
   (void)iedge; (void)oface



// ------------------------
// face2face
// ------------------------

// input : imesh, omesh, layer, f, iface
// output: oface
// return: void
#define metamesh_macro_face2face(IMESH,OMESH)\
   typename metamesh::internal::if_extrude_compatible<IMESH,OMESH,void>::type\
   face2face(\
      const IMESH &imesh,\
      const OMESH &omesh,\
      const std::size_t layer,\
      const std::size_t f,\
      const typename IMESH::face_t &iface,\
            typename OMESH::face_t &oface\
   )

#define metamesh_macro_face2face_param\
   (void)imesh; (void)omesh;\
   (void)layer; (void)f;\
   (void)iface; (void)oface



// ------------------------
// face2cell
// ------------------------

// input : imesh, omesh, layer, f, iface
// output: ocell
// return: void
#define metamesh_macro_face2cell(IMESH,OMESH)\
   typename metamesh::internal::if_extrude_compatible<IMESH,OMESH,void>::type\
   face2cell(\
      const IMESH &imesh,\
      const OMESH &omesh,\
      const std::size_t layer,\
      const std::size_t f,\
      const typename IMESH::face_t &iface,\
            typename OMESH::cell_t &ocell\
   )

#define metamesh_macro_face2cell_param\
   (void)imesh; (void)omesh;\
   (void)layer; (void)f;\
   (void)iface; (void)ocell

#endif
