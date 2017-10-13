/* -*- C++ -*- */

#ifndef METAMESH_KIP_AXIS
#define METAMESH_KIP_AXIS

/*
   This file provides the axis<> class and related functionality. Our goal
   is to provide a reasonably flexible mechanism by which users can easily
   include coordinate axes in their kip mesh renderings.

   Regarding terminology, consider the following two classes in the "kip"
   rendering code:

      model<real,base>
      scene<real,base,color>

   The template parameters of those types are:

      real    The floating-point type (typically, and by default, double)
              that kip uses for its computations.

      base    A general derived-from base class for kip shapes, similar
              to metamesh's node, edge, face, cell, and mesh bases.

      color   The output color, typically RGBA, for a kip-rendered bitmap.

   In typical usage, base is in fact a "color" type as well, usually RGB.
   Kip just calls it "base" for the same reason we do here, in metamesh,
   with the bases of nodes, edges, etc. So, one might think of "base" as
   an input color, and "color" as an output color.

   Now, here, in metamesh, we're about to define axis<>. The intention is
   to have a type from which users can produce shape specifications that,
   ultimately, go into a kip model<real,base>. In order to reflect this,
   we're going to use kip's terminology: <real,base>.

   Realize that "base," then, for our present purposes, should be thought
   of as a color. Indeed, for axis<>, we'll default it to metamesh::rgb,
   which is similar to kip's rgb class. (We don't use kip's rgb directly,
   so that axis<>, and a couple of other metamesh constructs, can operate
   independently of the kip library - say, to write a kip format file that
   is intended to be rendered later.) As for a kip scene<>'s color, don't
   worry about it here. It's for the output of kip's rendering, and is not
   relevant for shape/model specs.
*/



// =============================================================================
// Defaults
// =============================================================================

namespace metamesh {
namespace internal {
namespace {

   // origin
   const quad default_origin_diameter = 0.032L;
   const rgb  default_origin_color    = color::black;

   // line
   const quad default_line_length   = 1.000L;
   const quad default_line_diameter = 0.016L;

   const rgb  default_x_positive_color = color::brick_red;
   const rgb  default_x_negative_color = color::wild_watermelon;
   const rgb  default_y_positive_color = color::jungle_green;
   const rgb  default_y_negative_color = color::granny_smith_apple;
   const rgb  default_z_positive_color = color::denim;
   const rgb  default_z_negative_color = color::cornflower;

   // arrow
   const quad default_arrow_length   = 0.100L;
   const quad default_arrow_diameter = 0.032L;

   // tick
   const int  default_tick_n = 10;
   const quad default_tick_length   = 0.014L;
   const quad default_tick_diameter = 0.032L;
   const rgb  default_tick_color = color::gray_medium;

   // plane
   const quad default_plane_size = 0.25L;
   const std::pair<rgb,rgb> default_plane_color =
      std::make_pair(color::gray_light, color::gray_very_light);

}
}  // internal
}  // metamesh



// =============================================================================
// axis_line
// axis_tick
// axis_arrow
// axis_direction
// =============================================================================

namespace metamesh {
namespace internal {

// axis_line
template<class real, class base>
struct axis_line {
   bool on       = true;
   base color    = base(color::black);  // overridden for x, y, z
   real length   = real(default_line_length);
   real diameter = real(default_line_diameter);
};

// axis_tick
template<class real, class base>
struct axis_tick {
   bool on       = true;
   base color    = base(default_tick_color);
   real length   = real(default_tick_length);
   real diameter = real(default_tick_diameter);
   int  n        = default_tick_n;  // intentionally a signed int
};

// axis_arrow
template<class real, class base>
struct axis_arrow {
   bool on       = true;
   base color    = base(color::black);  // overridden for x, y, z
   real length   = real(default_arrow_length);
   real diameter = real(default_arrow_diameter);
};

// axis_direction
template<class real, class base>
struct axis_direction {
   bool on = true;
   axis_line <real,base> line;
   axis_tick <real,base> tick;
   axis_arrow<real,base> arrow;
};

}  // internal
}  // metamesh



// =============================================================================
// axis
// =============================================================================

namespace metamesh {
namespace kip {

template<
   #ifdef METAMESH_NO_DEFAULT
      class real, class base
   #else
      class real = default_real_t, class base = metamesh::rgb
   #endif
>
struct axis {
   using pair = std::pair<base,base>;

public:

   // types
   using real_t = real;
   using base_t = base;


   // ------------------------
   // Drawing parameters
   // ------------------------

   // on
   bool on = true;

   // scale
   real scale = real(1);

   // origin
   struct {
      bool on = true;
      real x = real(0);
      real y = real(0);
      real z = real(0);
      base color    = base(internal::default_origin_color);
      real diameter = real(internal::default_origin_diameter);
   } origin;

   // x
   struct {
      bool on = true;
      internal::axis_direction<real,base> positive, negative;
      struct {
         bool on = false;
         real x = real(0);
         pair color = pair(internal::default_plane_color);
         real ysize = real(internal::default_plane_size);
         real zsize = real(internal::default_plane_size);
         struct {
            real ysize = real(1);
            real zsize = real(1);  bool on = false;
         } box, ellipsoid;
      } plane;
   } x;

   // y
   struct {
      bool on = true;
      internal::axis_direction<real,base> positive, negative;
      struct {
         bool on = false;
         real y = real(0);
         pair color = pair(internal::default_plane_color);
         real xsize = real(internal::default_plane_size);
         real zsize = real(internal::default_plane_size);
         struct {
            real xsize = real(1);
            real zsize = real(1);  bool on = false;
         } box, ellipsoid;
      } plane;
   } y;

   // z
   struct {
      bool on = true;
      internal::axis_direction<real,base> positive, negative;
      struct {
         bool on = false;
         real z = real(0);
         pair color = pair(internal::default_plane_color);
         real xsize = real(internal::default_plane_size);
         real ysize = real(internal::default_plane_size);
         struct {
            real xsize = real(1);
            real ysize = real(1);  bool on = false;
         } box, ellipsoid;
      } plane;
   } z;


   // ------------------------
   // constructor, fix()
   // ------------------------

   // constructor
   explicit axis(void);

   // fix()
   void fix(void);
};

}  // kip
}  // metamesh



// =============================================================================
// constructor
// =============================================================================

namespace metamesh {
namespace kip {

template<class real, class base>
axis<real,base>::axis(void)
{
   // x
   x.positive.line .color = base(internal::default_x_positive_color);
   x.positive.arrow.color = base(internal::default_x_positive_color);
   x.negative.line .color = base(internal::default_x_negative_color);
   x.negative.arrow.color = base(internal::default_x_negative_color);

   // y
   y.positive.line .color = base(internal::default_y_positive_color);
   y.positive.arrow.color = base(internal::default_y_positive_color);
   y.negative.line .color = base(internal::default_y_negative_color);
   y.negative.arrow.color = base(internal::default_y_negative_color);

   // z
   z.positive.line .color = base(internal::default_z_positive_color);
   z.positive.arrow.color = base(internal::default_z_positive_color);
   z.negative.line .color = base(internal::default_z_negative_color);
   z.negative.arrow.color = base(internal::default_z_negative_color);
}

}  // kip
}  // metamesh



// =============================================================================
// fix: helper functions
// =============================================================================

namespace metamesh {
namespace internal {

// abs_false(value,bool)
// Sets value to its absolute value, and sets on = false if value == 0
template<class real>
inline void abs_false(real &value, bool &on)
{
   if ((value = std::abs(value)) == real(0))
      on = false;
}



// fix_side
template<class real, class SIDE>
void fix_side(SIDE &posneg)
{
   // line
   abs_false(posneg.line.diameter,  posneg.line.on);
   abs_false(posneg.line.length,    posneg.line.on);

   // tick
   abs_false(posneg.tick.diameter,  posneg.tick.on);
   abs_false(posneg.tick.length,    posneg.tick.on);
   if (posneg.tick.n < 0) posneg.tick.n = -posneg.tick.n;

   // arrow
   abs_false(posneg.arrow.diameter, posneg.arrow.on);
   abs_false(posneg.arrow.length,   posneg.arrow.on);

   // on
   if (!(posneg.line.on || posneg.tick.on || posneg.arrow.on))
      posneg.on = false;
}



// fix_direction
template<class real, class XYZ>
void fix_direction(XYZ &xyz)
{
   // positive, negative
   fix_side<real>(xyz.positive);
   fix_side<real>(xyz.negative);

   // on
   if (!(xyz.positive.on || xyz.negative.on || xyz.plane.on))
      xyz.on = false;
}

}  // internal
}  // metamesh



// =============================================================================
// fix
// =============================================================================

namespace metamesh {
namespace kip {

template<class real, class base>
void axis<real,base>::fix(void)
{
   // origin
   internal::abs_false(origin.diameter, origin.on);

   // planes: checkerboard sizes
   internal::abs_false(x.plane.ysize, x.plane.on);
   internal::abs_false(x.plane.zsize, x.plane.on);
   internal::abs_false(y.plane.xsize, y.plane.on);
   internal::abs_false(y.plane.zsize, y.plane.on);
   internal::abs_false(z.plane.xsize, z.plane.on);
   internal::abs_false(z.plane.ysize, z.plane.on);

   // planes: box/ellipsoid sizes
   internal::abs_false(x.plane.box.ysize, x.plane.box.on);
   internal::abs_false(x.plane.box.zsize, x.plane.box.on);
   internal::abs_false(y.plane.box.xsize, y.plane.box.on);
   internal::abs_false(y.plane.box.zsize, y.plane.box.on);
   internal::abs_false(z.plane.box.xsize, z.plane.box.on);
   internal::abs_false(z.plane.box.ysize, z.plane.box.on);

   internal::abs_false(x.plane.ellipsoid.ysize, x.plane.ellipsoid.on);
   internal::abs_false(x.plane.ellipsoid.zsize, x.plane.ellipsoid.on);
   internal::abs_false(y.plane.ellipsoid.xsize, y.plane.ellipsoid.on);
   internal::abs_false(y.plane.ellipsoid.zsize, y.plane.ellipsoid.on);
   internal::abs_false(z.plane.ellipsoid.xsize, z.plane.ellipsoid.on);
   internal::abs_false(z.plane.ellipsoid.ysize, z.plane.ellipsoid.on);

   // x, y, z
   internal::fix_direction<real>(x);
   internal::fix_direction<real>(y);
   internal::fix_direction<real>(z);

   // scale
   internal::abs_false(scale, on);

   // on
   if (!(origin.on || x.on || y.on || z.on))
      on = false;
}

}  // kip
}  // metamesh



// =============================================================================
// write_comment
// write_axis_line
// write_axis_tick
// write_axis_arrow
// write_axis
// =============================================================================

namespace metamesh {
namespace internal {

// write_comment(ostream,string)
void write_comment(std::ostream &s, const std::string &str)
{
   s << "\n// " << str << "\n";
}

// write_comment(ostream,string,width)
void write_comment(std::ostream &s, const std::string &str, const int width)
{
   if (width < 4) {
      s << "\n//"
        << "\n// " << str
        << "\n//\n";
   } else {
      const metamesh::loop n(width-3);
      s << "\n// ";
      while (n()) s << '=';
      s << "\n// " << str << "\n// ";
      while (n()) s << '=';
      s << "\n";
   }
}



// write_axis_line
template<class real, class base>
void write_axis_line(
   const metamesh::kip::axis<real,base> &axis,
   std::ostream &s, const point<real> &a, const point<real> &b,
   const real &r, const base &color
) {
   const point<real> center(axis.origin.x, axis.origin.y, axis.origin.z);
   s << "silo("
     << center + axis.scale*a << ", "
     << center + axis.scale*b << ", "
     << axis.scale*r << ", " << color << ")\n";
}



// write_axis_tick
template<class real, class base>
void write_axis_tick(
   const metamesh::kip::axis<real,base> &axis,
   std::ostream &s,
   const point<real> &a, const point<real> &b,

   // re: ticks
   const base &color,
   const real &tlen, const real &rlen, const int n,

   // re: arrow, origin
   const bool arrow,  const real &alen,
   const bool origin, const real &orad,

   // countptr (number of tickmarks)
   std::size_t *const countptr
) {
   const point<real> center(axis.origin.x, axis.origin.y, axis.origin.z);
   const point<real> v = b - a;
   const real vlen = metamesh::mod(v);  // == "line.length"
   if (!(vlen > 0)) return;
   const real delta = n > 0 ? vlen/n : 0;
   const point<real> r = op::half(tlen)*v/vlen;

   const metamesh::loop i(n+1);
   while (i()) {
      const point<real> c = a + real(i)*delta*v;
      const point<real> one = c-r;
      const point<real> two = c+r;

      // does tickmark overlap origin marker or arrow?
      if (origin && metamesh::mod(two-a) < orad + tlen) continue;
      if (arrow  && metamesh::mod(two-a) > vlen - alen) continue;

      // tickmark
      // The conditional is sort of a hack. We can call this function either to
      // actually write the tickmarks, or to accurately count how many tickmarks
      // would have been written, allowing callers to tweak certain comments to
      // reflect plural or singular "tickmark." ;-)
      if (countptr == nullptr)
         s << "spheroid("
           << center + axis.scale*one << ", "
           << center + axis.scale*two << ", "
           << axis.scale*rlen << ", " << color << ")\n";
      else
         (*countptr)++;
   }
}



// write_axis_arrow
template<class real, class base>
void write_axis_arrow(
   const metamesh::kip::axis<real,base> &axis,
   std::ostream &s, const point<real> &a, const point<real> &b,
   const real &r, const base &color
) {
   const point<real> center(axis.origin.x, axis.origin.y, axis.origin.z);
   s << "cone("
     << center + axis.scale*a << ", "
     << center + axis.scale*b << ", "
     << axis.scale*r << ", "
     << color << ")\n";
}



// write_axis
template<class real, class base, class PART>
void write_axis(
   std::ostream &s, const metamesh::kip::axis<real,base> &axis,
   const PART &part, const point<real> &tip, const std::string partstr
) {
   // lengths
   const real len = part.line .length;  // of line
   const real arr = part.arrow.length;  // of arrow

   // line length, possibly shortened by arrow length
   const real small = part.arrow.on ? len-arr : len;

   // line
   if (part.line.on && small > 0) {
      write_comment(s, partstr + " line");
      write_axis_line(
         axis,
         s, point<real>(0,0,0), small*tip,
         op::half(part.line.diameter), part.line.color
      );
   }

   // tickmarks
   if (part.tick.on) {
      std::size_t count = 0;
      for (std::size_t i = 0;  i < 2;  ++i) {
         if (i == 1) {
            if (count == 0) break;  // no tickmark(s); don't even print comment
            if (count == 1) write_comment(s, partstr + " tickmark");
            if (count >= 2) write_comment(s, partstr + " tickmarks");
         }
         write_axis_tick(
            axis,
            s, point<real>(0,0,0), len*tip,
            part.tick.color, part.tick.length,
            op::half(part.tick.diameter), part.tick.n,
            part.arrow.on, part.arrow.length,
            axis.origin.on, op::half(axis.origin.diameter),
            i == 0 ? &count : nullptr
         );
      }
   }

   // arrow
   if (part.arrow.on && arr > 0) {
      write_comment(s, partstr + " arrow");
      write_axis_arrow(
         axis,
         s, len*tip, small*tip,
         op::half(part.arrow.diameter), part.arrow.color
      );
   }
}

}  // internal
}  // metamesh



// =============================================================================
// write_axis_origin
// write_axis_x
// write_axis_y
// write_axis_z
// =============================================================================

namespace metamesh {
namespace internal {

// write_axis_origin
template<class real, class base>
void write_axis_origin(
   std::ostream &s,
   const metamesh::kip::axis<real,base> &axis
) {
   if (!axis.origin.on) return;
   write_comment(s, "origin", 27);

   // origin
   s << "\nsphere("
     << point<real>(axis.origin.x, axis.origin.y, axis.origin.z) << ", "
     << axis.scale*op::half(axis.origin.diameter) << ", "
     << axis.origin.color << ")\n";
}



// write_axis_x
template<class real, class base>
void write_axis_x(
   std::ostream &s,
   const metamesh::kip::axis<real,base> &axis
) {
   if (!axis.x.on) return;
   write_comment(s, "x axis", 27);

   // positive, negative
   if (axis.x.positive.on)
      write_axis(s, axis, axis.x.positive, point<real>(+1,0,0), "positive x");
   if (axis.x.negative.on)
      write_axis(s, axis, axis.x.negative, point<real>(-1,0,0), "negative x");

   // plane
   if (axis.x.plane.on) {
      s << "\n// plane\n";
      const point<real> center(axis.origin.x, axis.origin.y, axis.origin.z);

      const bool bon = axis.x.plane.box.on;
      const bool eon = axis.x.plane.ellipsoid.on;
      if (bon && eon) s << "ands(\n";
      else
      if (bon || eon) s << "and(\n";

      if (bon)
         s << "   box("
           << center + point<real>(axis.x.plane.x, 0, 0) << ", 0,0,0, "
           << axis.scale*point<real>(
                 0.001,
                 axis.x.plane.box.ysize,
                 axis.x.plane.box.zsize
              ) << "),\n";
      if (eon)
         s << "   ellipsoid("
           << center + point<real>(axis.x.plane.x, 0, 0) << ", 0,0,0, "
           << axis.scale*point<real>(
                 0.001,
                 axis.x.plane.ellipsoid.ysize,
                 axis.x.plane.ellipsoid.zsize
              ) << "),\n";

      // xplane
      s << (bon || eon ? "   " : "") << "xplane("
        << axis.origin.x + axis.x.plane.x << ", "
        << axis.scale*axis.x.plane.ysize << ","
        << axis.scale*axis.x.plane.zsize << ", "
        << axis.x.plane.color.first << ", "
        << axis.x.plane.color.second << (bon || eon ? ")\n)\n" : ")\n");
   }
}



// write_axis_y
template<class real, class base>
void write_axis_y(
   std::ostream &s,
   const metamesh::kip::axis<real,base> &axis
) {
   if (!axis.y.on) return;
   write_comment(s, "y axis", 27);

   // positive, negative
   if (axis.y.positive.on)
      write_axis(s, axis, axis.y.positive, point<real>(0,+1,0), "positive y");
   if (axis.y.negative.on)
      write_axis(s, axis, axis.y.negative, point<real>(0,-1,0), "negative y");

   // plane
   if (axis.y.plane.on) {
      s << "\n// plane\n";
      const point<real> center(axis.origin.x, axis.origin.y, axis.origin.z);

      const bool bon = axis.y.plane.box.on;
      const bool eon = axis.y.plane.ellipsoid.on;
      if (bon && eon) s << "ands(\n";
      else
      if (bon || eon) s << "and(\n";

      if (bon)
         s << "   box("
           << center + point<real>(0, axis.y.plane.y, 0) << ", 0,0,0, "
           << axis.scale*point<real>(
                 axis.y.plane.box.xsize,
                 0.001,
                 axis.y.plane.box.zsize
              ) << "),\n";
      if (eon)
         s << "   ellipsoid("
           << center + point<real>(0, axis.y.plane.y, 0) << ", 0,0,0, "
           << axis.scale*point<real>(
                 axis.y.plane.ellipsoid.xsize,
                 0.001,
                 axis.y.plane.ellipsoid.zsize
              ) << "),\n";

      // yplane
      s << (bon || eon ? "   " : "") << "yplane("
        << axis.origin.y + axis.y.plane.y << ", "
        << axis.scale*axis.y.plane.xsize << ","
        << axis.scale*axis.y.plane.zsize << ", "
        << axis.y.plane.color.first << ", "
        << axis.y.plane.color.second << (bon || eon ? ")\n)\n" : ")\n");
   }
}



// write_axis_z
template<class real, class base>
void write_axis_z(
   std::ostream &s,
   const metamesh::kip::axis<real,base> &axis
) {
   if (!axis.z.on) return;
   write_comment(s, "z axis", 27);

   // positive, negative
   if (axis.z.positive.on)
      write_axis(s, axis, axis.z.positive, point<real>(0,0,+1), "positive z");
   if (axis.z.negative.on)
      write_axis(s, axis, axis.z.negative, point<real>(0,0,-1), "negative z");

   // plane
   if (axis.z.plane.on) {
      s << "\n// plane\n";
      const point<real> center(axis.origin.x, axis.origin.y, axis.origin.z);

      const bool bon = axis.z.plane.box.on;
      const bool eon = axis.z.plane.ellipsoid.on;
      if (bon && eon) s << "ands(\n";
      else
      if (bon || eon) s << "and(\n";

      if (bon)
         s << "   box("
           << center + point<real>(0, 0, axis.z.plane.z) << ", 0,0,0, "
           << axis.scale*point<real>(
                 axis.z.plane.box.xsize,
                 axis.z.plane.box.ysize,
                 0.001
              ) << "),\n";
      if (eon)
         s << "   ellipsoid("
           << center + point<real>(0, 0, axis.z.plane.z) << ", 0,0,0, "
           << axis.scale*point<real>(
                 axis.z.plane.ellipsoid.xsize,
                 axis.z.plane.ellipsoid.ysize,
                 0.001
              ) << "),\n";

      // zplane
      s << (bon || eon ? "   " : "") << "zplane("
        << axis.origin.z + axis.z.plane.z << ", "
        << axis.scale*axis.z.plane.xsize << ","
        << axis.scale*axis.z.plane.ysize << ", "
        << axis.z.plane.color.first << ", "
        << axis.z.plane.color.second << (bon || eon ? ")\n)\n" : ")\n");
   }
}

}  // internal
}  // metamesh



// =============================================================================
// std::ostream << axis
// =============================================================================

namespace metamesh {
namespace kip {

template<class real, class base>
std::ostream &operator<<(
   std::ostream &s,
   const metamesh::kip::axis<real,base> &_axis
) {
   static const std::string during = "Detected during std::ostream << axis";

   // fix (first; can affect axis.on)
   metamesh::kip::axis<real,base> axis = _axis;
   axis.fix();

   // on
   if (!axis.on)
      return s;

   // begin
   internal::write_comment(s, "axis: begin", 80);

   // origin
   internal::write_axis_origin(s,axis);
   if (!s) return error("Problem encountered while writing origin", during), s;

   // x, y, z
   internal::write_axis_x(s,axis);
   if (!s) return error("Problem encountered while writing x axis", during), s;

   internal::write_axis_y(s,axis);
   if (!s) return error("Problem encountered while writing y axis", during), s;

   internal::write_axis_z(s,axis);
   if (!s) return error("Problem encountered while writing z axis", during), s;

   // done
   internal::write_comment(s, "axis: end", 80);
   return s << std::flush;
}

}  // kip
}  // metamesh



// =============================================================================
// metamesh::kip::ostream << axis
// =============================================================================

namespace metamesh {
namespace kip {

// In principle, I could allow the metamesh::kip::ostream and the metamesh::
// kip::axis to have different template parameters - say, kreal and kbase for
// the former, versus areal and abase for the latter). However, doing so might
// imply that the ostream's values would be used for output (the 'o' in ostream
// meaning, well, 'output'), but that isn't the case: this function basically
// just does some bookkeeping, then forwards to std::ostream << axis above!
// Which, effectively, means that the template parameters of axis are used.
template<class real, class base>
metamesh::kip::ostream<real,base> &operator<<(
   metamesh::kip::ostream<real,base>       &kstream,
   metamesh::kip::axis   <real,base> const &axis
) {
   // check stream
   if (!kstream.stream) {
      error("metamesh::kip::ostream's wrapped std::ostream "
            "is in a fail state",
            "Detected during metamesh::kip::ostream << axis");
      return kstream;
   }

   // write
   kstream.highlighting();
   kstream.stream << axis;  // std::ostream version (above)
   return kstream;
}

}  // kip
}  // metamesh

#endif
