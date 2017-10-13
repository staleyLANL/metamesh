/* -*- C++ -*- */

#ifndef METAMESH_KIP_STREAM
#define METAMESH_KIP_STREAM

// This file provides metamesh::kip::ostream and related functionality.
// Don't confuse this ostream with the kip library's, or with C++'s.

// Regarding terminology, see the discussion in metamesh-kip-axis.h.
// The remarks for axis apply to ostream as well.



// =============================================================================
// Defaults
// =============================================================================

namespace metamesh {
namespace internal {
namespace {

   // node
   const quad default_node_diameter = 0.10L;
   const rgb  default_node_color    = color::brick_red;

   // edge
   const quad default_edge_diameter = 0.06L;
   const quad default_edge_one      = 0.00L;
   const quad default_edge_two      = 0.00L;
   const rgb  default_edge_color    = color::gray_medium;

   const quad default_edge_link_floor_diameter = 1.2L*default_node_diameter;
   const quad default_edge_link_floor_length   = 0.02L;
   const rgb  default_edge_link_floor_color    = default_edge_color;
   const quad default_edge_link_arrow_diameter = default_node_diameter;
   const quad default_edge_link_arrow_length   = 0.20L;
   const rgb  default_edge_link_arrow_color    = default_edge_color;

   // face
   const quad default_face_diameter = 0.16L;
   const quad default_face_length   = 0.04L;
   const rgb  default_face_color    = color::cerulean;

   const quad default_face_link_diameter = 0.04L;
   const quad default_face_link_one      = 0.00L;
   const quad default_face_link_two      = 0.00L;
   const rgb  default_face_link_color    = color::white;

   // cell
   const point<quad> default_cell_size  = point<quad>(0.2L, 0.2L, 0.2L);
   const point<quad> default_cell_angle = point<quad>(0.0L, 0.0L, 0.0L);
   const rgb         default_cell_color = color::forest_green;

   const quad default_cell_link_diameter = 0.04L;
   const quad default_cell_link_one      = 0.00L;
   const quad default_cell_link_two      = 0.00L;
   const rgb  default_cell_link_color    = color::unmellow_yellow;

}
}  // internal
}  // metamesh



// =============================================================================
// ostream
// =============================================================================

namespace metamesh {
namespace kip {

// We say BASE, not base, for the second template argument,
// because some of the data members are called "base."
template<
   #ifdef METAMESH_NO_DEFAULT
      class real, class BASE
   #else
      // qqq Might modify axis (and its file comment) like we did here...
      #ifdef KIP_RENDERER
         class real = default_real_t, class BASE = ::kip::rgb
      #else
         class real = default_real_t, class BASE = metamesh::rgb
      #endif
   #endif
>
struct ostream {

   // types
   using real_t = real;
   using base_t = BASE;


   // ------------------------
   // Drawing parameters
   // ------------------------

   // on
   bool on = true;

   // scale
   real scale = real(1);

   // node
   struct {
      bool on       = true;
      real diameter = real(internal::default_node_diameter);
      BASE color    = BASE(internal::default_node_color);
      struct {
         bool on = true;
      } base;
   } node;

   // edge, links
   struct {
      bool on       = true;
      real diameter = real(internal::default_edge_diameter);
      real begin    = real(internal::default_edge_one);
      real end      = real(internal::default_edge_two);
      BASE color    = BASE(internal::default_edge_color);
      struct {
         struct {
            bool on       = false;
            real diameter = real(internal::default_edge_link_floor_diameter);
            real length   = real(internal::default_edge_link_floor_length);
            BASE color    = BASE(internal::default_edge_link_floor_color);
         } floor;
         struct {
            bool on       = false;
            real diameter = real(internal::default_edge_link_arrow_diameter);
            real length   = real(internal::default_edge_link_arrow_length);
            BASE color    = BASE(internal::default_edge_link_arrow_color);
         } arrow;
      } link;
      struct {
         bool on = true;
      } base;
   } edge;

   // face, links
   struct {
      bool on       = true;
      real diameter = real(internal::default_face_diameter);
      real length   = real(internal::default_face_length);
      BASE color    = BASE(internal::default_face_color);
      struct {
         bool on       = false;
         real diameter = real(internal::default_face_link_diameter);
         real begin    = real(internal::default_face_link_one);
         real end      = real(internal::default_face_link_two);
         BASE color    = BASE(internal::default_face_link_color);
      } link;
      struct {
         bool on = true;
      } base;
   } face;

   // cell, links
   struct {
      bool on           = true;
      point<real> size  = point<real>(internal::default_cell_size);
      point<real> angle = point<real>(internal::default_cell_angle);
      BASE        color = BASE       (internal::default_cell_color);
      struct {
         bool on       = false;
         real diameter = real(internal::default_cell_link_diameter);
         real begin    = real(internal::default_cell_link_one);
         real end      = real(internal::default_cell_link_two);
         BASE color    = BASE(internal::default_cell_link_color);
      } link;
      struct {
         bool on = true;
      } base;
   } cell;

   // base
   struct {
      bool on = true;
   } base;


   // ------------------------
   // Canned color schemes
   // ------------------------

   // default
   inline void default_colors(void)
   {
      node.color            = BASE(internal::default_node_color);
      edge.color            = BASE(internal::default_edge_color);
      edge.link.floor.color = BASE(internal::default_edge_link_floor_color);
      edge.link.arrow.color = BASE(internal::default_edge_link_arrow_color);
      face.color            = BASE(internal::default_face_color);
      face.link.color       = BASE(internal::default_face_link_color);
      cell.color            = BASE(internal::default_cell_color);
      cell.link.color       = BASE(internal::default_cell_link_color);
   }

   // crayola "silver swirls"
   inline void silver_swirls(void)
   {
      node.color            = BASE(color::rusty_red);
      edge.color            = BASE(color::granite_gray);
      edge.link.floor.color = edge.color;
      edge.link.arrow.color = edge.color;
      face.color            = BASE(color::cerulean_frost);
      face.link.color       = BASE(color::white);
      cell.color            = BASE(color::shiny_shamrock);
      cell.link.color       = BASE(color::aztec_gold);
   }

   // crayola "gem tones"
   inline void gem_tones(void)
   {
      node.color            = BASE(color::smokey_topaz);
      edge.color            = BASE(color::onyx);
      edge.link.floor.color = edge.color;
      edge.link.arrow.color = edge.color;
      face.color            = BASE(color::lapis_lazuli);
      face.link.color       = BASE(color::white);
      cell.color            = BASE(color::emerald);
      cell.link.color       = BASE(color::peridot);
   }

   // crayola "pearl brite"
   inline void pearl_brite(void)
   {
      node.color            = BASE(color::salmon_pearl);
      edge.color            = BASE(color::black_coral_pearl);
      edge.link.floor.color = edge.color;
      edge.link.arrow.color = edge.color;
      face.color            = BASE(color::turquoise_pearl);
      face.link.color       = BASE(color::white);
      cell.color            = BASE(color::ocean_green_pearl);
      cell.link.color       = BASE(color::sunny_pearl);
   }

   // crayola "metallic fx"
   inline void metallic_fx(void)
   {
      node.color            = BASE(color::big_dip_o_ruby);
      edge.color            = BASE(color::sonic_silver);
      edge.link.floor.color = edge.color;
      edge.link.arrow.color = edge.color;
      face.color            = BASE(color::steel_blue);
      face.link.color       = BASE(color::white);
      cell.color            = BASE(color::illuminating_emerald);
      cell.link.color       = BASE(color::gold_fusion);
   }


   // ------------------------
   // Bounding box
   // ------------------------

   struct {
      // Should bounds be computed (regardless of whether or
      // not they're displayed - line.on and corner.on below)
      bool compute = false;

      // line
      struct {
         bool on       = false;
         real diameter = real(0.8)*real(internal::default_edge_diameter);
         BASE color    = BASE(color::gray_light);
      } line;

      // corner
      struct {
         bool on       = false;
         real diameter = real(0.8)*real(internal::default_node_diameter);
         struct {
            struct {
               struct { BASE color = BASE(rgb(  0,   0,   0)); } zmin;
               struct { BASE color = BASE(rgb(  0,   0, 255)); } zmax;
            } ymin;
            struct {
               struct { BASE color = BASE(rgb(  0, 255,   0)); } zmin;
               struct { BASE color = BASE(rgb(  0, 255, 255)); } zmax;
            } ymax;
         } xmin;
         struct {
            struct {
               struct { BASE color = BASE(rgb(255,   0,   0)); } zmin;
               struct { BASE color = BASE(rgb(255,   0, 255)); } zmax;
            } ymin;
            struct {
               struct { BASE color = BASE(rgb(255, 255,   0)); } zmin;
               struct { BASE color = BASE(rgb(255, 255, 255)); } zmax;
            } ymax;
         } xmax;
      } corner;

      // bounds
      point<real> min = point<real>(real(0),real(0),real(0)), &minimum = min;
      point<real> avg = point<real>(real(0),real(0),real(0)), &average = avg;
      point<real> max = point<real>(real(0),real(0),real(0)), &maximum = max;
   } bound;


   // ------------------------
   // Proceed-mode constructs.
   // Makes write() behave in
   // certain ways if the same
   // mesh is sent repeatedly.
   // ------------------------

   // proceed
   bool proceed = false;

   // node, edge, face, cell
   // Previous "end" (in the iterator sense) becomes next "begin"
   struct {
      std::size_t node = 0;
      std::size_t edge = 0;
      std::size_t face = 0;
      std::size_t cell = 0;
   } begin;


   // ------------------------
   // Re: syntax-highlighting
   // ------------------------

   bool wrote_highlighting = false;

   // syntax highlighting for emacs, maybe other editors;
   // kip files somewhat resemble C/C++
   inline void highlighting(void)
   {
      if (!wrote_highlighting)
         stream << "/* -*- C++ -*- */\n";
      wrote_highlighting = true;
   }


   // ------------------------
   // Data, constructor
   // ------------------------

   // wrapped ostream
   std::ostream &stream;

   // kip #included
   #if defined(KIP_RENDERER)

      // constructor
      inline explicit ostream(
         std::ostream &s, ::kip::model<real_t,base_t> *const m = nullptr
      ) : stream(s), model_ptr(m)
      { }

      // push
      // SHAPE should be a shape from the kip library
      template<class SHAPE>
      inline bool push(const SHAPE &shape) const
      {
         return model_ptr != nullptr ? model_ptr->push(shape), true : false;
      }

      // has_scene
      inline bool has_scene(void) const
      {
         return model_ptr != nullptr;
      }

      private: ::kip::model<real_t,base_t> *const model_ptr;

   // kip NOT #included
   #else
      // constructor
      inline explicit ostream(std::ostream &s) : stream(s) { }
   #endif
};

}  // kip
}  // metamesh

#endif
