/* -*- C++ -*- */

#ifndef METAMESH_IMAGE
#define METAMESH_IMAGE

// This file provides functionality for writing images to raw .rgb image files.
// Such files contain absolutely nothing except raw data - RGB values for each
// pixel of an image. We support the writing of raw .rgb images because they're
// easy to write, and they can be converted easily to other image formats with
// available software such as ImageMagick and PhotoShop.
//
// We originally placed our image class into metamesh::kip, as it was intended
// to be part of our interface to the "kip" rendering package, which can create
// images in the first place. The class and its basic functionality, however,
// don't actually require the presence of the kip library. So, we decided to
// place image directly into the metamesh namespace.



// =============================================================================
// image
// =============================================================================

namespace metamesh {

class image {

   // ------------------------
   // Data - private
   // ------------------------

   // good
   bool good = true;  // until/unless there's a file-name problem

   // re: file name
   std::string name;  // file name
   std::string ext;   // file extension

   // re: multiple files
   std::size_t ndigits;   // for multiple files: number of digits for frame#s
   bool   multiple;  // flag: do we plan to write multiple files?

   // bookkeeping
   std::size_t counter = 0;  // for multiple files
   bool   written = false;


   // ------------------------
   // ctor
   // Helper for constructors
   // Compute ext, name, good
   // ------------------------

   inline void ctor(const std::string &n, const std::string &x)
   {
      // ext
      //    ""     ==> ""
      //    "."    ==> "."
      //    ".rgb" ==> ".rgb"
      //    "rgb"  ==> ".rgb"
      ext = ((x.size() == 0 || x[0] == '.') ? "" : ".") + x;

      // name
      if (multiple)
         name = n;  // separate name and ext; frame#s put between them later
      else
         name = n + ext;  // full file name; we won't be using frame numbers

      // check
      // File names will be (or are) blank?
      if (( multiple && name == "" && ndigits == 0 && ext == "") ||
          (!multiple && name == "")) {
         metamesh::error(
            "The given name [and extension] will result in blank file name(s)",
            "Detected during construction of metamesh::image"
         );
         good = false;
      }
   }


   // ------------------------
   // Data - public
   // ------------------------

public:

   // flip image top-to-bottom?
   bool flip = true;


   // ------------------------
   // Constructors
   // ------------------------

   // Single-file case
   //    name
   //    name, ext
   inline explicit image(
      const std::string &_name,
      const std::string &_ext = ".rgb"
   ) {
      ndigits = 0;  multiple = false;
      ctor(_name,_ext);
   }

   // Multiple-file case
   //    name, num
   //    name, num, ext
   inline explicit image(
      const std::string &_name, std::size_t num,
      const std::string &_ext = ".rgb"
   ) {
      ndigits = 1;  multiple = true;
      while (num /= 10) ndigits++;
      ctor(_name,_ext);
   }


   // ------------------------
   // write()
   // ------------------------

   template<class color>
   void write(
      const color *const ptr,
      const std::size_t hpixel,
      const std::size_t vpixel,
      const std::string &context
   );
};

}  // metamesh



// =============================================================================
// write_image_line
// =============================================================================

namespace metamesh {
namespace internal {

template<class color>
bool write_image_line(
   std::ofstream &ofs, const color *const ptr, const std::size_t hpixel,
   std::size_t row, const std::string &filename, const std::string &context
) {
   for (std::size_t h = row*hpixel;  h < (row+1)*hpixel;  ++h) {
      unsigned char pixel[3];
      pixel[0] = metamesh::rgb(ptr[h]).r;
      pixel[1] = metamesh::rgb(ptr[h]).g;
      pixel[2] = metamesh::rgb(ptr[h]).b;

      if (!ofs.write((const char *)pixel, std::streamsize(3))) {
         metamesh::error(
            "Error writing r,g,b values to file \"" + filename +
            "\"; bailing out", context);
         return false;
      }
   }
   return true;
}

}  // internal
}  // metamesh



// =============================================================================
// image::write
// =============================================================================

namespace metamesh {

template<class color>
void image::write(
   const color *const ptr, const std::size_t hpixel, const std::size_t vpixel,
   const std::string &context
) {
   // good?
   if (!good) {
      metamesh::error(
        "Cannot write to file; image object was constructed "
        "with blank file name",
         context
      );
      return;
   }

   // filename
   std::string filename;

   if (multiple) {
      // multiple files
      std::ostringstream oss;
      oss << std::setfill('0') << std::setw(int(ndigits)) << counter++;
      filename = name + oss.str() + ext;
   } else {
      // single file
      if (written)
         metamesh::warning(
           "Overwriting file with new image; "
           "perhaps you wanted image multi-file mode?",
            context
         );
      filename = name;
   }

   // open file
   std::ofstream ofs(filename, std::ofstream::binary);
   if (!ofs) {
      metamesh::error(
         "Unable to open file \"" + filename + "\" to write rgb values",
          context
      );
      return;
   }

   // write
   const metamesh::loop v(vpixel);
   if (flip) {
      while (v.back())  // top down
         if (!internal::write_image_line(ofs,ptr,hpixel,v,filename,context))
            break;
   } else {
      while (v.fore())  // bottom up
         if (!internal::write_image_line(ofs,ptr,hpixel,v,filename,context))
            break;
   }

   // done
   written = true;
}

}  // metamesh

#endif
