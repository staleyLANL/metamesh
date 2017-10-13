/* -*- C++ -*- */

#ifndef METAMESH_TUPLE
#define METAMESH_TUPLE

// This file provides
//    tuple
//    tuple<0> (specialization)
//    zero
//    one, two, ..., twelve
//    some
// and related classes and functionality.



// =============================================================================
// tup
// index_to
// =============================================================================

namespace metamesh {

// tup_enum
namespace internal {
   enum tup_enum { tup_enum_unused };
}

// tup
metamesh_make_global(internal::tup_enum, tup, tup_enum_unused)



// index_to
// Wrap a T, considered to be some sort of "index" to a basis
template<
   #ifdef METAMESH_NO_DEFAULT
      class basis, class T
   #else
      class basis, class T = std::size_t
   #endif
>
class index_to {
   T value;
public:
   // default
   inline explicit index_to(void)
   {
   }

   // from T
   inline explicit index_to(const T &_value) : value(_value)
   {
   }

   // assignment from T
   inline index_to &operator=(const T &_value)
   {
      value = _value;
      return *this;
   }

   // convert to T
   inline operator T(void) const
   {
      return value;
   }
};



// istream >> index_to
template<class basis, class T>
inline std::istream &operator>>(
   std::istream &s,
   metamesh::index_to<basis,T> &obj
) {
   T value;
   s >> value;
   obj = value;
   return s;
}

}  // metamesh



// =============================================================================
// ifstubvoid
// Helper class
// =============================================================================

namespace metamesh {
namespace internal {

   // T --> T
   template<class T>
   class ifstubvoid {
   public:
      using type = T;
   };

   // stub --> void
   template<>
   class ifstubvoid<stub> {
   public:
      using type = void;
   };

}  // internal
}  // metamesh



// =============================================================================
// tuple
//    n     == size of the tuple
//    basis == node etc. to embed in tuple, to get edge/face/cell "terms"
//    T     == type stored in the tuple, e.g. it's a tuple of std::size_t values
// For n = 1, 2, ... (the 0 case is specialized later)
// =============================================================================

namespace metamesh {

template<
   #ifdef METAMESH_NO_DEFAULT
      std::size_t n, class basis, class T
   #else
      std::size_t n, class basis, class T = std::size_t
   #endif
>
class tuple {

   // data
   // Embedded in index_to<>, to preserve basis (e.g. a node),
   // not just T (an index)
   index_to<basis,T> value[n];

public:

   // has_const_size
   // size
   // basis_t
   // qqq Eventually, may want to have a static const std::size_t to replace
   // has_const_size. We'd probably want -1 if there simply is no fixed
   // size, or >= 0 to indicate the fixed size if there is one.
   static const bool has_const_size = true;
   inline std::size_t size(void) const
   {
      return n;
   }
   using basis_t = basis;



   // tuple()
   inline explicit tuple(void)
   { }

   // tuple(tuple<n,stub,Tfrom>)
   // Implicit construction from "generic" same-length tuple with basis=void
   // and type Tfrom - probably coming from operator, (comma operator). Note
   // that we don't genericize the "from" tuple's basis, as that would allow,
   // for instance, a tuple for nodes to construct from one for edges, which
   // probably isn't something we'd intend. Neither, of course, can n differ.
   template<class Tfrom>
   inline tuple(
      const tuple<
         n,
         stub,
         Tfrom
      > &from
   ) {
      const loop i(n);
      while (i())
         (*this)[i] = T(from[i]);
   }

   template<class Tfrom>
   inline tuple(
      const tuple<
         n,
         typename internal::ifstubvoid<basis>::type,
         Tfrom
      > &from
   ) {
      const loop i(n);
      while (i())
         (*this)[i] = T(from[i]);
   }



   // operator[]
   inline       index_to<basis,T> &operator[](const std::size_t i)
   {
      metamesh_assert(i < size());
      return value[i];
   }
   inline const index_to<basis,T> &operator[](const std::size_t i) const
   {
      metamesh_assert(i < size());
      return value[i];
   }



   // clear
   inline void clear(void)
   {
      // nothing to do, for a (fixed-size!) tuple
   }

   // prepare
   inline void prepare(const std::size_t want)
   {
      // qqq Eventually, instead of doing an exit (!!!), we should probably
      // have this function return true or false, indicating whether or not
      // it was able to resize to the wanted size. I'd say that eventually,
      // also, for a well-defined interface, clear() (above) should probably
      // also return something, probably true or false. Then, for both of
      // these functions, the caller can decide on an appropriate course of
      // action - probably a diagnostic.

      // Because tuple's size is compile-time fixed...
      if (want != size()) {
         std::ostringstream oss;
         oss << "tuple<" << size() << "> was asked to hold "
             <<  want << (want == 1 ? " value" : " values");
         metamesh::error(oss, "");
      }
   }



   // read(istream, std::size_t)
   // Read from istream into value[i], which is of type index_to<basis,T>,
   // which is basically a wrapped T
   inline std::istream &read(
      std::istream &s, const std::size_t i,
      const std::string & /*context*/ = ""
   ) {
      metamesh_assert(i < size());
      return s >> value[i];
   }

   // push(T, std::size_t)
   // Similar to read(), but we have the T value itself, not an istream
   // from which to read it
   inline index_to<basis,T> &push(
      const T &val, const std::size_t i,
      const std::string & /*context*/ = ""
   ) {
      metamesh_assert(i < size());
      return value[i] = index_to<basis,T>(val);
   }
};

// has_const_size
template<std::size_t n, class basis, class T>
const bool tuple<n,basis,T>::has_const_size;

}  // metamesh



// =============================================================================
// tuple<0>
// Specialization <n=0> of the general tuple as defined above.
// =============================================================================

namespace metamesh {

template<class basis, class T>
class tuple<0,basis,T> {
public:

   // has_const_size
   // size
   // basis_t
   static const bool has_const_size = true;
   inline std::size_t size(void) const
   {
      return 0;
   }
   using basis_t = basis;



   // tuple()
   inline explicit tuple(void)
   {
   }

   // tuple(tup_enum)
   // Implicit construction from (tup), for consistency with n > 0 tuple's
   // having construction from operator, (comma operator) based generic tuples
   inline tuple(const internal::tup_enum &)
   {
   }

   template<class Tfrom>
   inline tuple(
      const tuple<
         0,
         typename internal::ifstubvoid<basis>::type,
         Tfrom
      > &
   ) {
   }



   // operator[]
   // Here for completeness; shouldn't be called
   inline       index_to<basis,T> &operator[](const std::size_t)
   {
      metamesh::error("tuple<0>'s operator[] can't be meaningfully called", "");
      static       index_to<basis,T> tmp;
      return tmp;
   }
   inline const index_to<basis,T> &operator[](const std::size_t) const
   {
      metamesh::error("tuple<0>'s operator[] can't be meaningfully called", "");
      static const index_to<basis,T> tmp;
      return tmp;
   }



   // clear
   inline void clear(void)
   {
      // nothing to do, for a (fixed-size!) tuple
   }

   // prepare
   inline void prepare(const std::size_t want)
   {
      // qqq Same remark as for generic tuple defined earlier.

      // Because tuple's size is compile-time fixed...
      if (want != size()) {
         std::ostringstream oss;
         oss << "tuple<" << size() << "> was asked to hold "
             <<  want << (want == 1 ? " value" : " values");
         metamesh::error(oss, "");
      }
   }



   // read(istream, std::size_t)
   // Here for completeness; shouldn't be called
   // qqq Here and elsewhere above and below, should make use of "context"
   inline std::istream &read(
      std::istream &s, const std::size_t,
      const std::string & /*context*/ = ""
   ) {
      metamesh::error("tuple<0>'s read() can't be meaningfully called", "");
      return s;
   }

   // push(T, std::size_t)
   // Here for completeness; shouldn't be called
   inline index_to<basis,T> &push(
      const T &, const std::size_t,
      const std::string & /*context*/ = ""
   ) {
      metamesh::error("tuple<0>'s push() can't be meaningfully called", "");
      static index_to<basis,T> tmp;
      return tmp;
   }
};

// has_const_size
template<class basis, class T>
const bool tuple<0,basis,T>::has_const_size;

}  // metamesh



// =============================================================================
// Functions involving tuple
//    find
//    istream>>
//    ostream<<
//    operator,
// =============================================================================

namespace metamesh {

// find
// Is value in tuple?
template<std::size_t n, class basis, class T, class VALUE>
inline bool find(const tuple<n,basis,T> &obj, const VALUE &value)
{
   const loop i(obj);
   while (i())
      if (obj[i] == T(value))
         return true;
   return false;
}



// istream >> tuple
template<std::size_t n, class basis, class T>
std::istream &operator>>(
   std::istream &s, metamesh::tuple<n,basis,T> &obj
) {
   // read values
   const metamesh::loop i(n);
   while (i())
      if (!(s >> obj[i]))
         break;

   // done
   return s;
}

// ostream << tuple
template<std::size_t n, class basis, class T>
std::ostream &operator<<(
   std::ostream &s, const metamesh::tuple<n,basis,T> &obj
) {
   bool first = true;

   // write values
   const metamesh::loop i(n);
   while (i()) {
      if (!(s << (first ? "" : " ") << obj[i]))
         break;
      first = false;
   }

   // done
   return s;
}

}  // metamesh



// tup,T
// Bootstrap a tuple
template<class T>
metamesh::tuple<1,metamesh::stub,T> operator,(
   const metamesh::internal::tup_enum &,  // as for tup
   const T &value
) {
   metamesh::tuple<1,metamesh::stub,T> out;
   out[0] = value;
   return out;
}

// tuple,T
// Append to a tuple
template<std::size_t n, class basis, class T>
metamesh::tuple<n+1,basis,T> operator,(
   const metamesh::tuple<n,basis,T> &from,
   const T &value
) {
   metamesh::tuple<n+1,basis,T> out;
   const metamesh::loop i(n);
   while (i())
      out[i] = from[i];
   out[n] = value;
   return out;
}



// =============================================================================
// zero
// one
// two
// ...
// twelve
// =============================================================================

namespace metamesh {

// Macro: metamesh_make_tuple_header
// Helps make the "header" for various types
#ifdef METAMESH_NO_DEFAULT
   #define metamesh_make_tuple_header(classname,n)\
      template<class basis, class T>\
      class classname : public tuple<n,basis,T>
#else
   #define metamesh_make_tuple_header(classname,n)\
      template<class basis, class T = std::size_t>\
      class classname : public tuple<n,basis,T>
#endif



// Macro: metamesh_make_tuple_contents
// Helps make the "contents" for various types
#define metamesh_make_tuple_contents(classname,n)\
      using base = tuple<n,basis,T>;\
   \
   public:\
      inline explicit classname(void) { }\
      \
      template<class Tfrom>\
      inline classname(const tuple<n,metamesh::stub,Tfrom> &from) :\
         base(from) { }\
      \
      template<class Tfrom>\
      inline classname(\
         const tuple<n,typename internal::ifstubvoid<basis>::type,Tfrom> &from\
      ) :\
         base(from) { }



// ------------------------
// zero
// ------------------------

metamesh_make_tuple_header(zero,0) {
   using base = tuple<0,basis,T>;

public:
   inline explicit zero(void) { }

   inline zero(const internal::tup_enum &)
   { }

   template<class Tfrom>
   inline zero(
      const tuple<
         0,
         typename internal::ifstubvoid<basis>::type,
         Tfrom
      > &from
   ) :
      base(from) { }
};



// ------------------------
// one
// ------------------------

metamesh_make_tuple_header(one,1) {
   metamesh_make_tuple_contents(one,1)

   inline explicit one(
      const T &v0
   ) {
      (*this)[0] = v0;
   }
};



// ------------------------
// two
// ------------------------

metamesh_make_tuple_header(two,2) {
   metamesh_make_tuple_contents(two,2)

   inline explicit two(
      const T &v0, const T &v1
   ) {
      (*this)[0] = v0;  (*this)[1] = v1;
   }
};



// ------------------------
// three
// ------------------------

metamesh_make_tuple_header(three,3) {
   metamesh_make_tuple_contents(three,3)

   inline explicit three(
      const T &v0, const T &v1, const T &v2
   ) {
      (*this)[0] = v0;  (*this)[1] = v1;  (*this)[2] = v2;
   }
};



// ------------------------
// four
// ------------------------

metamesh_make_tuple_header(four,4) {
   metamesh_make_tuple_contents(four,4)

   inline explicit four(
      const T &v0, const T &v1, const T &v2, const T &v3
   ) {
      (*this)[0] = v0;  (*this)[1] = v1;  (*this)[2] = v2;  (*this)[3] = v3;
   }
};



// ------------------------
// five
// ------------------------

metamesh_make_tuple_header(five,5) {
   metamesh_make_tuple_contents(five,5)

   inline explicit five(
      const T &v0, const T &v1, const T &v2, const T &v3,
      const T &v4
   ) {
      (*this)[0] = v0;  (*this)[1] = v1;  (*this)[2] = v2;  (*this)[3] = v3;
      (*this)[4] = v4;
   }
};



// ------------------------
// six
// ------------------------

metamesh_make_tuple_header(six,6) {
   metamesh_make_tuple_contents(six,6)

   inline explicit six(
      const T &v0, const T &v1, const T &v2, const T &v3,
      const T &v4, const T &v5
   ) {
      (*this)[0] = v0;  (*this)[1] = v1;  (*this)[2] = v2;  (*this)[3] = v3;
      (*this)[4] = v4;  (*this)[5] = v5;
   }
};



// ------------------------
// seven
// ------------------------

metamesh_make_tuple_header(seven,7) {
   metamesh_make_tuple_contents(seven,7)

   inline explicit seven(
      const T &v0, const T &v1, const T &v2, const T &v3,
      const T &v4, const T &v5, const T &v6
   ) {
      (*this)[0] = v0;  (*this)[1] = v1;  (*this)[2] = v2;  (*this)[3] = v3;
      (*this)[4] = v4;  (*this)[5] = v5;  (*this)[6] = v6;
   }
};



// ------------------------
// eight
// ------------------------

metamesh_make_tuple_header(eight,8) {
   metamesh_make_tuple_contents(eight,8)

   inline explicit eight(
      const T &v0, const T &v1, const T &v2, const T &v3,
      const T &v4, const T &v5, const T &v6, const T &v7
   ) {
      (*this)[0] = v0;  (*this)[1] = v1;  (*this)[2] = v2;  (*this)[3] = v3;
      (*this)[4] = v4;  (*this)[5] = v5;  (*this)[6] = v6;  (*this)[7] = v7;
   }
};



// ------------------------
// nine
// ------------------------

metamesh_make_tuple_header(nine,9) {
   metamesh_make_tuple_contents(nine,9)

   inline explicit nine(
      const T &v0, const T &v1, const T &v2, const T &v3,
      const T &v4, const T &v5, const T &v6, const T &v7,
      const T &v8
   ) {
      (*this)[0] = v0;  (*this)[1] = v1;  (*this)[2] = v2;  (*this)[3] = v3;
      (*this)[4] = v4;  (*this)[5] = v5;  (*this)[6] = v6;  (*this)[7] = v7;
      (*this)[8] = v8;
   }
};



// ------------------------
// ten
// ------------------------

metamesh_make_tuple_header(ten,10) {
   metamesh_make_tuple_contents(ten,10)

   inline explicit ten(
      const T &v0, const T &v1, const T &v2, const T &v3,
      const T &v4, const T &v5, const T &v6, const T &v7,
      const T &v8, const T &v9
   ) {
      (*this)[0] = v0;  (*this)[1] = v1;  (*this)[2] = v2;  (*this)[3] = v3;
      (*this)[4] = v4;  (*this)[5] = v5;  (*this)[6] = v6;  (*this)[7] = v7;
      (*this)[8] = v8;  (*this)[9] = v9;
   }
};



// ------------------------
// eleven
// ------------------------

metamesh_make_tuple_header(eleven,11) {
   metamesh_make_tuple_contents(eleven,11)

   inline explicit eleven(
      const T &v0, const T &v1, const T &v2, const T &v3,
      const T &v4, const T &v5, const T &v6, const T &v7,
      const T &v8, const T &v9, const T &v10
   ) {
      (*this)[0] = v0;  (*this)[1] = v1;  (*this)[2] = v2;  (*this)[3] = v3;
      (*this)[4] = v4;  (*this)[5] = v5;  (*this)[6] = v6;  (*this)[7] = v7;
      (*this)[8] = v8;  (*this)[9] = v9;  (*this)[10]=v10;
   }
};



// ------------------------
// twelve
// ------------------------

metamesh_make_tuple_header(twelve,12) {
   metamesh_make_tuple_contents(twelve,12)

   inline explicit twelve(
      const T &v0, const T &v1, const T &v2, const T &v3,
      const T &v4, const T &v5, const T &v6, const T &v7,
      const T &v8, const T &v9, const T &v10,const T &v11
   ) {
      (*this)[0] = v0;  (*this)[1] = v1;  (*this)[2] = v2;  (*this)[3] = v3;
      (*this)[4] = v4;  (*this)[5] = v5;  (*this)[6] = v6;  (*this)[7] = v7;
      (*this)[8] = v8;  (*this)[9] = v9;  (*this)[10]=v10;  (*this)[11]=v11;
   }
};

#undef metamesh_make_tuple_header
#undef metamesh_make_tuple_contents

}  // metamesh



// =============================================================================
// some
// Like tuple, but with a dynamic size
// =============================================================================

namespace metamesh {

// qqq You know, maybe this std::size_t default should be set up in the same
// way as, say, default_real_t is set up. Maybe, say, default_index_t.
template<
   #ifdef METAMESH_NO_DEFAULT
      class basis, class T
   #else
      class basis, class T = std::size_t
   #endif
>
class some {

   // data
   // Embedded in index_to<>, to preserve basis (e.g. a node),
   // not just T (an index)
   std::vector<index_to<basis,T>> value;

public:

   // has_const_size
   // size
   // basis_t
   static const bool has_const_size = false;
   inline std::size_t size(void) const
   {
      return value.size();
   }
   using basis_t = basis;



   // some()
   inline explicit some(void)
   {
   }

   // some(tuple<n,stub,Tfrom>)
   // Implicit construction from "generic" any-length tuple with basis=void
   // and type Tfrom - probably coming from operator, (comma operator)
   template<std::size_t n, class Tfrom>
   inline some(
      const tuple<
         n,
         stub,
         Tfrom
      > &from
   ) {
      prepare(n);
      const loop i(n);
      while (i())
         value.push_back(index_to<basis,T>(T(from[i])));
   }

   // some(tuple<n,basis,Tfrom>)
   // Implicit construction from "generic" any-length tuple with same basis
   // and type Tfrom.
   template<std::size_t n, class Tfrom>
   inline some(
      const tuple<
         n,
         typename internal::ifstubvoid<basis>::type,
         Tfrom
      > &from
   ) {
      prepare(n);
      const loop i(n);
      while (i())
         value.push_back(index_to<basis,T>(T(from[i])));
   }

   // some(some<basis,Tfrom>)
   template<class Tfrom>
   inline some(const some<basis,Tfrom> &from)
   {
      const std::size_t n = from.size();
      prepare(n);
      const loop i(n);
      while (i())
         value.push_back(index_to<basis,T>(T(from[i])));
   }

   // some(tup)
   inline some(const internal::tup_enum &)
   {
   }



   // operator[]
   inline       index_to<basis,T> &operator[](const std::size_t i)
   {
      metamesh_assert(i < size());
      return value[i];
   }
   inline const index_to<basis,T> &operator[](const std::size_t i) const
   {
      metamesh_assert(i < size());
      return value[i];
   }



   // clear
   inline void clear(void)
   {
      value.clear();
   }

   // prepare
   inline void prepare(const std::size_t want)
   {
      value.clear();
      value.reserve(want);
   }



   // read(istream, std::size_t)
   inline std::istream &read(
      std::istream &s, const std::size_t i,
      const std::string &context = ""
   ) {
      // should have i == size()
      if (i != size()) {
         std::ostringstream oss;
         oss << "Out-of-sequence call to some::read(istream,i=" << i
             << "); current size()=" << size();
         metamesh::error(oss,context);
      }

      // read
      T val;
      if (s >> val)
         push(val);
      return s;
   }

   // push(T, std::size_t)
   inline index_to<basis,T> &push(
      const T &val, const std::size_t i,
      const std::string &context = ""
   ) {
      // should have i == size()
      if (i != size()) {
         std::ostringstream oss;
         oss << "Out-of-sequence call to some::push(value,i=" << i
             << "); current size()=" << size();
         metamesh::error(oss,context);
      }

      // push
      return push(val);
   }

   // push(T)
   inline index_to<basis,T> &push(const T &val)
   {
      value.push_back(index_to<basis,T>(val));
      return value.back();
   }
};

// has_const_size
template<class basis, class T>
const bool some<basis,T>::has_const_size;

}  // metamesh



// =============================================================================
// Functions involving some
//    find
//    istream>>
//    ostream<<
// =============================================================================

namespace metamesh {

// find
// Is value in some?
template<class basis, class T, class VALUE>
bool find(const some<basis,T> &obj, const VALUE &value)
{
   const loop i(obj);
   while (i())
      if (obj[i] == T(value))
         return true;
   return false;
}



// istream >> some
template<class basis, class T>
std::istream &operator>>(
   std::istream &s, metamesh::some<basis,T> &obj
) {
   // read length
   std::size_t n;
   if (!(s >> n))
      return s;
   obj.prepare(n);

   // read values
   const metamesh::loop i(n);
   while (i()) {
      T tmp;
      if (!(s >> tmp))
         break;
      obj.push(tmp,i);
   }

   // done
   return s;
}



// ostream << some
template<class basis, class T>
std::ostream &operator<<(
   std::ostream &s, const metamesh::some<basis,T> &obj
) {
   // write length
   const std::size_t n = obj.size();
   if (!(s << n << (n ? "  " : "")))
      return s;

   // write values
   const metamesh::loop i(n);
   while (i())
      if (!(s << " " << obj[i]))
         break;

   // done
   return s;
}

}  // metamesh

#endif
