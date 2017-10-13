/* -*- C++ -*- */

#ifndef METAMESH_EXTRUDE
#define METAMESH_EXTRUDE

// This file provides user-callable extrude() functions for 0-form to 1-form,
// 1-form to 2-form, and 2-form to 3-form extrusions.

// This was #defined elsewhere
#undef metamesh_form2form

// Whole file
namespace metamesh {



// =============================================================================
// consistent_basis
// =============================================================================

namespace internal {

// default
template<class A, class B, class T>
class consistent_basis { };


// node, node (of possibly different varieties)
template<
   class aterms, class abase,
   class bterms, class bbase, class T
>
class consistent_basis<
   node<aterms,abase>,
   node<bterms,bbase>, T
> { public: using type = T; };


// edge, edge (of possibly different varieties)
template<
   class aterms, class abase,
   class bterms, class bbase, class T
>
class consistent_basis<
   edge<aterms,abase>,
   edge<bterms,bbase>, T
> { public: using type = T; };

}  // internal



// =============================================================================
// extrude 0-1
// =============================================================================

template<
   class inode, class iedge, class iface, class icell, class ibase,
   class onode, class oedge, class oface, class ocell, class obase,
   class PATH,
   class MORE,
   class NODE_ON   = internal::mask_class,
   class ACTION    = internal::noop_class,
   class NODE2NODE = internal::noop_class,
   class NODE2EDGE = internal::noop_class
>
inline   mesh<onode,oedge,oface,ocell,obase,1> &extrude(
   const mesh<inode,iedge,iface,icell,ibase,0> &in,
   /* */ mesh<onode,oedge,oface,ocell,obase,1> &out,
   const PATH      &path,
   const MORE      &more,
   const tie_t      tying,
   const trim_t     trimming  = metamesh::trim,
   const NODE_ON   &node_on   = metamesh::on,
   const ACTION    &action    = metamesh::noop,
   const NODE2NODE &node2node = metamesh::noop,
   const NODE2EDGE &node2edge = metamesh::noop
) {
   void *ptr;
   return internal::extrude01(
      ptr,
      in,
      path, more,
      node_on,
      out,
      tying, trimming,
      action,
      node2node, node2edge
   );
}

template<
   class inode, class iedge, class iface, class icell, class ibase,
   class onode, class oedge, class oface, class ocell, class obase,
   class PATH,
   class MORE,
   class NODE_ON   = internal::mask_class,
   class ACTION    = internal::noop_class,
   class NODE2NODE = internal::noop_class,
   class NODE2EDGE = internal::noop_class
>
inline   mesh<onode,oedge,oface,ocell,obase,1> &extrude(
   const internal::extrude_info<
      metamesh::mesh<inode,iedge,iface,icell,ibase,0>,
      metamesh::mesh<onode,oedge,oface,ocell,obase,1>,
      1
   > * &ptr,
   const mesh<inode,iedge,iface,icell,ibase,0> &in,
   /* */ mesh<onode,oedge,oface,ocell,obase,1> &out,
   const PATH      &path,
   const MORE      &more,
   const tie_t      tying,
   const trim_t     trimming  = metamesh::trim,
   const NODE_ON   &node_on   = metamesh::on,
   const ACTION    &action    = metamesh::noop,
   const NODE2NODE &node2node = metamesh::noop,
   const NODE2EDGE &node2edge = metamesh::noop
) {
   return internal::extrude01(
      ptr,
      in,
      path, more,
      node_on,
      out,
      tying, trimming,
      action,
      node2node, node2edge
   );
}



// =============================================================================
// extrude 1-2
// =============================================================================

template<
   class inode, class iedge, class iface, class icell, class ibase,
   class onode, class oedge, class oface, class ocell, class obase,
   class PATH,
   class MORE,
   class NODE_ON   = internal::mask_class,
   class EDGE_ON   = internal::mask_class,
   class ACTION    = internal::noop_class,
   class NODE2NODE = internal::noop_class,
   class NODE2EDGE = internal::noop_class,
   class EDGE2EDGE = internal::noop_class,
   class EDGE2FACE = internal::noop_class
>
inline   mesh<onode,oedge,oface,ocell,obase,2> &extrude(
   const mesh<inode,iedge,iface,icell,ibase,1> &in,
   /* */ mesh<onode,oedge,oface,ocell,obase,2> &out,
   const PATH      &path,
   const MORE      &more,
   const tie_t      tying,
   const trim_t     trimming  = metamesh::trim,
   const NODE_ON   &node_on   = metamesh::on,
   const EDGE_ON   &edge_on   = metamesh::on,
   const ACTION    &action    = metamesh::noop,
   const NODE2NODE &node2node = metamesh::noop,
   const NODE2EDGE &node2edge = metamesh::noop,
   const EDGE2EDGE &edge2edge = metamesh::noop,
   const EDGE2FACE &edge2face = metamesh::noop
) {
   void *ptr;
   return internal::extrude12(
      ptr,
      in,
      path, more,
      node_on, edge_on,
      out,
      tying, trimming,
      action,
      node2node, node2edge,
      edge2edge, edge2face
   );
}

template<
   class inode, class iedge, class iface, class icell, class ibase,
   class onode, class oedge, class oface, class ocell, class obase,
   class PATH,
   class MORE,
   class NODE_ON   = internal::mask_class,
   class EDGE_ON   = internal::mask_class,
   class ACTION    = internal::noop_class,
   class NODE2NODE = internal::noop_class,
   class NODE2EDGE = internal::noop_class,
   class EDGE2EDGE = internal::noop_class,
   class EDGE2FACE = internal::noop_class
>
inline   mesh<onode,oedge,oface,ocell,obase,2> &extrude(
   const internal::extrude_info<
      metamesh::mesh<inode,iedge,iface,icell,ibase,1>,
      metamesh::mesh<onode,oedge,oface,ocell,obase,2>,
      2
   > * &ptr,
   const mesh<inode,iedge,iface,icell,ibase,1> &in,
   /* */ mesh<onode,oedge,oface,ocell,obase,2> &out,
   const PATH      &path,
   const MORE      &more,
   const tie_t      tying,
   const trim_t     trimming  = metamesh::trim,
   const NODE_ON   &node_on   = metamesh::on,
   const EDGE_ON   &edge_on   = metamesh::on,
   const ACTION    &action    = metamesh::noop,
   const NODE2NODE &node2node = metamesh::noop,
   const NODE2EDGE &node2edge = metamesh::noop,
   const EDGE2EDGE &edge2edge = metamesh::noop,
   const EDGE2FACE &edge2face = metamesh::noop
) {
   return internal::extrude12(
      ptr,
      in,
      path, more,
      node_on, edge_on,
      out,
      tying, trimming,
      action,
      node2node, node2edge,
      edge2edge, edge2face
   );
}



// =============================================================================
// extrude 2-3
// =============================================================================

template<
   class inode, class iedge, class iface, class icell, class ibase,
   class onode, class oedge, class oface, class ocell, class obase,
   class PATH,
   class MORE,
   class NODE_ON   = internal::mask_class,
   class EDGE_ON   = internal::mask_class,
   class FACE_ON   = internal::mask_class,
   class ACTION    = internal::noop_class,
   class NODE2NODE = internal::noop_class,
   class NODE2EDGE = internal::noop_class,
   class EDGE2EDGE = internal::noop_class,
   class EDGE2FACE = internal::noop_class,
   class FACE2FACE = internal::noop_class,
   class FACE2CELL = internal::noop_class
>
inline typename internal::consistent_basis<
   typename iface::basis_t,
   typename oface::basis_t,
   mesh<onode,oedge,oface,ocell,obase,3>
>::type &extrude(
   const mesh<inode,iedge,iface,icell,ibase,2> &in,
   /* */ mesh<onode,oedge,oface,ocell,obase,3> &out,
   const PATH      &path,
   const MORE      &more,
   const tie_t      tying,
   const trim_t     trimming  = metamesh::trim,
   const NODE_ON   &node_on   = metamesh::on,
   const EDGE_ON   &edge_on   = metamesh::on,
   const FACE_ON   &face_on   = metamesh::on,
   const ACTION    &action    = metamesh::noop,
   const NODE2NODE &node2node = metamesh::noop,
   const NODE2EDGE &node2edge = metamesh::noop,
   const EDGE2EDGE &edge2edge = metamesh::noop,
   const EDGE2FACE &edge2face = metamesh::noop,
   const FACE2FACE &face2face = metamesh::noop,
   const FACE2CELL &face2cell = metamesh::noop
) {
   void *ptr;
   return internal::extrude23(
      ptr,
      in,
      path, more,
      node_on, edge_on, face_on,
      out,
      tying, trimming,
      action,
      node2node, node2edge,
      edge2edge, edge2face,
      face2face, face2cell
   );
}

template<
   class inode, class iedge, class iface, class icell, class ibase,
   class onode, class oedge, class oface, class ocell, class obase,
   class PATH,
   class MORE,
   class NODE_ON   = internal::mask_class,
   class EDGE_ON   = internal::mask_class,
   class FACE_ON   = internal::mask_class,
   class ACTION    = internal::noop_class,
   class NODE2NODE = internal::noop_class,
   class NODE2EDGE = internal::noop_class,
   class EDGE2EDGE = internal::noop_class,
   class EDGE2FACE = internal::noop_class,
   class FACE2FACE = internal::noop_class,
   class FACE2CELL = internal::noop_class
>
inline typename internal::consistent_basis<
   typename iface::basis_t,
   typename oface::basis_t,
   mesh<onode,oedge,oface,ocell,obase,3>
>::type &extrude(
   const internal::extrude_info<
      metamesh::mesh<inode,iedge,iface,icell,ibase,2>,
      metamesh::mesh<onode,oedge,oface,ocell,obase,3>,
      3
   > * &ptr,
   const mesh<inode,iedge,iface,icell,ibase,2> &in,
   /* */ mesh<onode,oedge,oface,ocell,obase,3> &out,
   const PATH      &path,
   const MORE      &more,
   const tie_t      tying,
   const trim_t     trimming  = metamesh::trim,
   const NODE_ON   &node_on   = metamesh::on,
   const EDGE_ON   &edge_on   = metamesh::on,
   const FACE_ON   &face_on   = metamesh::on,
   const ACTION    &action    = metamesh::noop,
   const NODE2NODE &node2node = metamesh::noop,
   const NODE2EDGE &node2edge = metamesh::noop,
   const EDGE2EDGE &edge2edge = metamesh::noop,
   const EDGE2FACE &edge2face = metamesh::noop,
   const FACE2FACE &face2face = metamesh::noop,
   const FACE2CELL &face2cell = metamesh::noop
) {
   return internal::extrude23(
      ptr,
      in,
      path, more,
      node_on, edge_on, face_on,
      out,
      tying, trimming,
      action,
      node2node, node2edge,
      edge2edge, edge2face,
      face2face, face2cell
   );
}

}  // metamesh

#endif
