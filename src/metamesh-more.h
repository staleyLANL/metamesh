/* -*- C++ -*- */

#ifndef METAMESH_MORE
#define METAMESH_MORE

// This file provides classes that might be useful when writing extrusion
// continue-or-stop conditions. We don't have much here now, but may create
// additional functionality as we find out what users need.



// =============================================================================
// counter
// =============================================================================

namespace metamesh {

class counter {
   std::size_t num;

public:
   // counter(num)
   inline explicit counter(const std::size_t _num) : num(_num) { }

   // more
   template<class IMESH, class OMESH>
   inline metamesh_macro_more(IMESH,OMESH) const
   {
      metamesh_macro_more_param;
      return layer < num;
   }
};

}  // metamesh

#endif
