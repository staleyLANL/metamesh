/* -*- C++ -*- */

#ifndef METAMESH_RGB
#define METAMESH_RGB

// This file provides the rgb class.



// =============================================================================
// rgb
// =============================================================================

namespace metamesh {

class rgb {
   using uchar = unsigned char;

public:

   // ------------------------
   // Data
   // ------------------------

   union { uchar r, red;   };
   union { uchar g, green; };
   union { uchar b, blue;  };


   // ------------------------
   // Constructors
   // ------------------------

   // default
   inline explicit rgb(void) : r(0), g(0), b(0) { }

   // gray level
   inline explicit rgb(const uchar gray) :
      r(gray), g(gray), b(gray)
   { }

   // r, g, b
   inline explicit rgb(const uchar _r, const uchar _g, const uchar _b) :
      r(_r), g(_g), b(_b)
   { }

   // from certain kip classes
#if defined(KIP_RENDERER)
   // kip::RGB
   template<class T>
   inline explicit rgb(const kip::RGB<T> &from) :
      r(from.r), g(from.g), b(from.b)
   { }

   // kip::RGBA
   template<class T>
   inline explicit rgb(const kip::RGBA<T> &from) :
      r(from.r), g(from.g), b(from.b)
   { }

   // kip::crayola
   inline explicit rgb(const kip::crayola &from)
   {
      kip::rgb value = from;
      r = value.r;
      g = value.g;
      b = value.b;
   }
#endif


   // ------------------------
   // operator()(r,g,b)
   // for convenience
   // ------------------------

   inline rgb &operator()(
      const uchar &_r, const uchar &_g, const uchar &_b
   ) {
      r = _r;
      g = _g;
      b = _b;
      return *this;
   }


   // ------------------------
   // Conversion operators
   // to certain kip classes
   // ------------------------

#if defined(KIP_RENDERER)
   /*
   // convert to kip::rgb
   // convert to kip::rgba
   inline operator kip::rgb (void) const { return kip::rgb (r,g,b); }
   inline operator kip::rgba(void) const { return kip::rgba(r,g,b); }
   */

   // convert to kip::RGB<T>
   template<class T>
   inline operator kip::RGB<T>(void) const
   {
      return kip::RGB<T>(T(r), T(g), T(b));
   }

   // convert to kip::RGBA<T>
   template<class T>
   inline operator kip::RGBA<T>(void) const
   {
      return kip::RGBA<T>(T(r), T(g), T(b));
   }

   /*
   // Convert to kip::marble<uchar,real>
   template<class real>
   inline operator kip::marble<uchar,real>(void) const
   {
      return kip::marble<uchar,real>(
         r, g, b,
         1.5,1, 0.01,1, 1,unsigned(1000000*drand48()), false
      );
   }
   */
#endif
};



// ostream << rgb
inline std::ostream &operator<<(std::ostream &s, const metamesh::rgb &obj)
{
   // convert r,g,b to unsigned, so they won't print as characters
   return s
      << unsigned(obj.r) << ','
      << unsigned(obj.g) << ','
      << unsigned(obj.b);
}

}  // metamesh

#endif
