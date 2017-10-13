/* -*- C++ -*- */

#ifndef METAMESH_KIP_SCENE
#define METAMESH_KIP_SCENE

// This file provides functions for writing metamesh mesh constructs into
// kip::scene objects. Use of this functionality requires the kip library.



// =============================================================================
// scene
//    Derives from kip::scene, for rendering.
//    Derives from metamesh::kip::ostream, for mesh-drawing parameters.
// The metamesh::kip::ostream must wrap a std::ostream. We'll provide
// a std::ostringstream to satisfy its purposes.
// =============================================================================

namespace metamesh {
namespace kip {

template<
   class real  = metamesh::default_real_t,
   class base  = ::kip::default_tag_t,
   class color = ::kip::default_color_t
>
class scene :
   public ::kip::scene<real,base,color>,
   public ::metamesh::kip::ostream<real,base>
{
   // metamesh::kip::ostream base
   // Provides the necessary information (e.g. object sizes and scaling)
   // for a metamesh mesh (which knows nothing about kip) to be written
   // into the base ::kip::scene (which knows nothing about metamesh).

public:

   // std::ostringstream
   // For use by the metamesh::kip::ostream
   std::ostringstream oss;

   // Constructor
   inline explicit scene(void) : metamesh::kip::ostream<real,base>(oss,this)
   { }

   // operator()
   // Retrieve kip::scene
   inline       ::kip::scene<real,base,color> &operator()(void)
      { return *this; }
   inline const ::kip::scene<real,base,color> &operator()(void) const
      { return *this; }

   // ostream()
   // Retrieve metamesh::kip::ostream
   inline       ::metamesh::kip::ostream<real,base> &ostream(void)
      { return *this; }
   inline const ::metamesh::kip::ostream<real,base> &ostream(void) const
      { return *this; }

   // render
   inline scene &render(void)
   {
      ::kip::trace(*this);
      return *this;
   }
};

}  // kip
}  // metamesh



// =============================================================================
// Summary of operator<<
//    kip::scene << metamesh::kip::axis
//    metamesh::kip::scene << metamesh::kip::axis
//    metamesh::kip::scene << metamesh::mesh
//    metamesh::image << kip::scene
// These are in the upcoming blocks.
// =============================================================================

// =============================================================================
// kip::scene << metamesh::kip::axis
// metamesh::kip::scene << metamesh::kip::axis
//
// Note: that we have both is analogous to the fact that we have axis stream
// output to std::ostream AND metamesh::kip::ostream; see metamesh-kip-axis.h.
// Because axis already has the necessary kip template parameters, as well as
// data members for describing the output axis representation, it can be sent
// directly to a std::ostream or kip::scene without needing the added template
// information in a metamesh::kip::ostream or metamesh::kip::scene.
// =============================================================================

// use namespace of axis (RHS in both cases)
namespace metamesh {
namespace kip {

// kip::scene << metamesh::kip::axis
template<
   class sreal, class sbase, class scolor,  // prefix "s" for scene
   class areal, class abase                 // prefix "a" for axis
>
::kip::scene<sreal,sbase,scolor> &operator<<(
   ::kip::scene<sreal,sbase,scolor> &scene,
   const metamesh::kip::axis<areal,abase> &axis
) {
   // place axis into kip-readable string
   std::ostringstream oss;
   oss << axis;

   // create istringstream for input to model
   std::istringstream iss(oss.str());
   iss >> scene.model();

   // done
   scene.append = false;  // make user reset later if they really want it!
   return scene;
}



// metamesh::kip::scene << metamesh::kip::axis
template<
   class sreal, class sbase, class scolor,
   class areal, class abase
>
metamesh::kip::scene<sreal,sbase,scolor> &operator<<(
   metamesh::kip::scene<sreal,sbase,scolor> &scene,
   const metamesh::kip::axis<areal,abase> &axis
) {
   // forward to kip::scene << metamesh::kip::axis
   scene() << axis;  // above
   return scene;
}

}  // kip
}  // metamesh



// =============================================================================
// metamesh::kip::scene << metamesh::mesh
//
// For mesh, unlike for axis (see above), we have metamesh::kip::scene output
// only, not kip::scene output as well. The latter is unavailable because mesh,
// unlike axis, is a fundamental metamesh-specific class that does not contain
// information on how to represent itself in any particular rendering output.
// The metamesh::kip::ostream class does, however, have that information, and
// so does metamesh::kip::scene, which derives from metamesh::kip::ostream.
// =============================================================================

// use namespace of mesh (RHS)
namespace metamesh {

template<
   class sreal, class sbase, class scolor,
   class NODE, class EDGE, class FACE, class CELL, class BASE, std::size_t FORM
>
metamesh::kip::scene<sreal,sbase,scolor> &operator<<(
   metamesh::kip::scene<sreal,sbase,scolor> &scene,
   const metamesh::mesh<NODE,EDGE,FACE,CELL,BASE,FORM> &mesh
) {
   // cleanup - pre
   scene.oss.str("");  // reset string to empty
   scene.oss.clear();  // clear any error flags

   if (!scene.append)
      scene.clear();
   scene.append = true;  //  ==> get direct-entered and ostringstream-entered

   // Write mesh to kip stream; elements might go directly to kip scene, if
   // kip is #includes. Some may in any event go to middleman ostringstream
   // in scene.oss.
   scene.ostream() << mesh;

   // qqq Actually, the next thing should be done piece-by-piece earlier;
   // probably in write_mesh_base, write_form, write_bounds.

   // Transfer any remaining ostringstream scene.oss contents.
   std::istringstream iss(scene.oss.str());
   iss >> scene.model();

   // cleanup - post
   scene.oss.str("");  // reset string to empty
   scene.oss.clear();  // clear any error flags

   // done
   scene.append = false;  // make user reset later if they really want it!
   return scene;
}

}  // metamesh



// =============================================================================
// metamesh::image << kip::scene
// Automatically handles metamesh::image << metamesh::kip::scene, because the
// latter derives from kip::scene - and the LHS (metamesh::image) is the same,
// and thus still returns what we expect from operator<<.
// =============================================================================

// use namespace of image (LHS)
namespace metamesh {

template<class real, class base, class color>
inline metamesh::image &operator<<(
   metamesh::image &image,
   const ::kip::scene<real,base,color> &scene
) {
   image.write(
      scene(), scene.hpixel, scene.vpixel,
     "Detected during call to metamesh::image << kip::scene"
   );
   return image;
}

}  // metamesh

#endif
