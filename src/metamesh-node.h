/* -*- C++ -*- */

#ifndef METAMESH_NODE
#define METAMESH_NODE

// This file provides the node class and related functionality.



// =============================================================================
// iclass
// node
// =============================================================================

namespace metamesh {

// iclass
template<std::size_t n>
class iclass { };

// node
template<
   #ifdef METAMESH_NO_DEFAULT
   class  terms,
   class  base,
   std::size_t dimension = std::size_t(terms::dimension)
   #else
   class  terms,
   class  base = default_base_t,
   std::size_t dimension = std::size_t(terms::dimension)
   #endif
>
class node { };

}  // metamesh



// =============================================================================
// node<terms,base,0>
// =============================================================================

namespace metamesh {

template<class _terms, class _base>
class node<_terms,_base,0> :
   public _terms,
   public _base
{
public:
   // dimension
   static const std::size_t dimension = 0;

   // types
   using value_t =  typename _terms::value_t;
   using terms_t = _terms;
   using base_t  = _base;

   // label
   static inline const char *label(void) { return "node"; }


   // ------------------------
   // Constructors
   // ------------------------

   // node()
   // node(terms)
   inline explicit node(
      const terms_t &terms = terms_t()
   ) :
      terms_t(terms),
      base_t {}
   { }

   // node(base)
   inline explicit node(
      const base_t &base
   ) :
      terms_t{},
      base_t (base)
   { }

   // node(terms,base)
   inline explicit node(
      const terms_t &terms,
      const base_t  &base
   ) :
      terms_t(terms),
      base_t (base)
   { }


   // ------------------------
   // Miscellaneous
   // ------------------------

   // assignment to terms/base
   inline node &operator=(const terms_t &from) { return terms() = from, *this; }
   inline node &operator=(const base_t  &from) { return base () = from, *this; }

   // retrieve terms/base
   inline       terms_t &terms(void)       { return *this; }
   inline const terms_t &terms(void) const { return *this; }
   inline       base_t  &base (void)       { return *this; }
   inline const base_t  &base (void) const { return *this; }

   // operator()()
   // here for consistency with operator() for 1d, 2d, and 3d nodes.
   inline node &operator()(
      void
   ) {
      return *this;
   }


   // ------------------------
   // check
   // ------------------------

   inline diagnostic_t check(const std::string &context = "") const
   {
      const diagnostic_t
         base_check = base().check(internal::new_context(
            "Detected during node.check's examination of base", context
         ));

      // remember, error < warning < note < good
      return metamesh::min(base_check);
   }
};

// dimension
template<class _terms, class _base>
const std::size_t node<_terms,_base,0>::dimension;

}  // metamesh



// =============================================================================
// node<terms,base,1>
// =============================================================================

namespace metamesh {

template<class _terms, class _base>
class node<_terms,_base,1> :
   public _terms,
   public _base
{
public:
   // dimension
   static const std::size_t dimension = 1;

   // types
   using value_t =  typename _terms::value_t;
   using terms_t = _terms;
   using base_t  = _base;

   // label
   static inline const char *label(void) { return "node"; }

   // using
   using terms_t::value;
   using terms_t::label;


   // ------------------------
   // Constructors
   // ------------------------

   // node()
   // node(terms)
   inline explicit node(
      const terms_t &terms = terms_t()
   ) :
      terms_t(terms),
      base_t {}
   { }

   // node(base)
   inline explicit node(
      const base_t &base
   ) :
      terms_t{},
      base_t (base)
   { }

   // node(terms,base)
   inline explicit node(
      const terms_t &terms,
      const base_t  &base
   ) :
      terms_t(terms),
      base_t (base)
   { }

   // node(a)
   // node(a,base)
   inline explicit node(
      const value_t &a,
      const base_t  &base = base_t()
   ) :
      terms_t(a),
      base_t (base)
   { }


   // ------------------------
   // Miscellaneous
   // ------------------------

   // assignment to terms/base
   inline node &operator=(const terms_t &from) { return terms() = from, *this; }
   inline node &operator=(const base_t  &from) { return base () = from, *this; }

   // retrieve terms/base
   inline       terms_t &terms(void)       { return *this; }
   inline const terms_t &terms(void) const { return *this; }
   inline       base_t  &base (void)       { return *this; }
   inline const base_t  &base (void) const { return *this; }

   // operator()(a)
   // shorthand assignment to component
   inline node &operator()(
      const value_t &a
   ) {
      value(component<0>()) = a;
      return *this;
   }


   // ------------------------
   // check
   // ------------------------

   inline diagnostic_t check(const std::string &context = "") const
   {
      static const std::string msg =
         "Detected during node.check's examination of coordinate ";

      const value_t &a = value(component<0>());

      const std::string &laba = terms().label(component<0>());

      const diagnostic_t
         acheck = internal::check_floating(
            a, internal::new_context(msg + laba, context)),
         base_check = base().check(internal::new_context(
            "Detected during node.check's examination of base", context
         ));

      // remember, error < warning < note < good
      return metamesh::min(acheck, base_check);
   }
};

// dimension
template<class _terms, class _base>
const std::size_t node<_terms,_base,1>::dimension;

}  // metamesh



// =============================================================================
// node<terms,base,2>
// =============================================================================

namespace metamesh {

template<class _terms, class _base>
class node<_terms,_base,2> :
   public _terms,
   public _base
{
public:
   // dimension
   static const std::size_t dimension = 2;

   // types
   using value_t =  typename _terms::value_t;
   using terms_t = _terms;
   using base_t  = _base;

   // label
   static inline const char *label(void) { return "node"; }

   // using
   using terms_t::value;
   using terms_t::label;


   // ------------------------
   // Constructors
   // ------------------------

   // node()
   // node(terms)
   inline explicit node(
      const terms_t &terms = terms_t()
   ) :
      terms_t(terms),
      base_t {}
   { }

   // node(base)
   inline explicit node(
      const base_t &base
   ) :
      terms_t{},
      base_t (base)
   { }

   // node(terms,base)
   inline explicit node(
      const terms_t &terms,
      const base_t  &base
   ) :
      terms_t(terms),
      base_t (base)
   { }

   // node(a,b)
   // node(a,b,base)
   inline explicit node(
      const value_t &a, const value_t &b,
      const base_t  &base = base_t()
   ) :
      terms_t(a,b),
      base_t (base)
   { }


   // ------------------------
   // Miscellaneous
   // ------------------------

   // assignment to terms/base
   inline node &operator=(const terms_t &from) { return terms() = from, *this; }
   inline node &operator=(const base_t  &from) { return base () = from, *this; }

   // retrieve terms/base
   inline       terms_t &terms(void)       { return *this; }
   inline const terms_t &terms(void) const { return *this; }
   inline       base_t  &base (void)       { return *this; }
   inline const base_t  &base (void) const { return *this; }

   // operator()(a,b)
   // shorthand assignment to components
   inline node &operator()(
      const value_t &a,
      const value_t &b
   ) {
      value(component<0>()) = a;
      value(component<1>()) = b;
      return *this;
   }


   // ------------------------
   // check
   // ------------------------

   inline diagnostic_t check(const std::string &context = "") const
   {
      static const std::string msg =
         "Detected during node.check's examination of coordinate ";

      const value_t &a = value(component<0>());
      const value_t &b = value(component<1>());

      const std::string &laba = terms().label(component<0>());
      const std::string &labb = terms().label(component<1>());

      const diagnostic_t
         acheck = internal::check_floating(
            a, internal::new_context(msg + laba, context)),
         bcheck = internal::check_floating(
            b, internal::new_context(msg + labb, context)),
         base_check = base().check(internal::new_context(
            "Detected during node.check's examination of base", context
         ));

      // remember, error < warning < note < good
      return metamesh::min(acheck, bcheck, base_check);
   }
};

// dimension
template<class _terms, class _base>
const std::size_t node<_terms,_base,2>::dimension;

}  // metamesh



// =============================================================================
// node<terms,base,3>
// =============================================================================

namespace metamesh {

template<class _terms, class _base>
class node<_terms,_base,3> :
   public _terms,
   public _base
{
public:
   // dimension
   static const std::size_t dimension = 3;

   // types
   using value_t =  typename _terms::value_t;
   using terms_t = _terms;
   using base_t  = _base;

   // label
   static inline const char *label(void) { return "node"; }

   // using
   using terms_t::value;
   using terms_t::label;


   // ------------------------
   // Constructors
   // ------------------------

   // node()
   // node(terms)
   inline explicit node(
      const terms_t &terms = terms_t()
   ) :
      terms_t(terms),
      base_t {}
   { }

   // node(base)
   inline explicit node(
      const base_t &base
   ) :
      terms_t{},
      base_t (base)
   { }

   // node(terms,base)
   inline explicit node(
      const terms_t &terms,
      const base_t  &base
   ) :
      terms_t(terms),
      base_t (base)
   { }

   // node(a,b,c)
   // node(a,b,c,base)
   inline explicit node(
      const value_t &a, const value_t &b, const value_t &c,
      const base_t  &base = base_t()
   ) :
      terms_t(a,b,c),
      base_t (base)
   { }


   // ------------------------
   // Miscellaneous
   // ------------------------

   // assignment to terms/base
   inline node &operator=(const terms_t &from) { return terms() = from, *this; }
   inline node &operator=(const base_t  &from) { return base () = from, *this; }

   // retrieve terms/base
   inline       terms_t &terms(void)       { return *this; }
   inline const terms_t &terms(void) const { return *this; }
   inline       base_t  &base (void)       { return *this; }
   inline const base_t  &base (void) const { return *this; }

   // operator()(a,b,c)
   // shorthand assignment to components
   inline node &operator()(
      const value_t &a,
      const value_t &b,
      const value_t &c
   ) {
      value(component<0>()) = a;
      value(component<1>()) = b;
      value(component<2>()) = c;
      return *this;
   }


   // ------------------------
   // check
   // ------------------------

   inline diagnostic_t check(const std::string &context = "") const
   {
      static const std::string msg =
         "Detected during node.check's examination of coordinate ";

      const value_t &a = value(component<0>());
      const value_t &b = value(component<1>());
      const value_t &c = value(component<2>());

      const std::string &laba = terms().label(component<0>());
      const std::string &labb = terms().label(component<1>());
      const std::string &labc = terms().label(component<2>());

      const diagnostic_t
         acheck = internal::check_floating(
            a, internal::new_context(msg + laba, context)),
         bcheck = internal::check_floating(
            b, internal::new_context(msg + labb, context)),
         ccheck = internal::check_floating(
            c, internal::new_context(msg + labc, context)),
         base_check = base().check(internal::new_context(
            "Detected during node.check's examination of base", context
         ));

      // remember, error < warning < note < good
      return metamesh::min(acheck, bcheck, ccheck, base_check);
   }
};

// dimension
template<class _terms, class _base>
const std::size_t node<_terms,_base,3>::dimension;

}  // metamesh



// =============================================================================
// node_coord
// =============================================================================

namespace metamesh {
namespace internal {

// input: base
template<class terms, class base, std::size_t dimension>
inline bool node_coord(
   std::istream &, metamesh::node<terms,base,dimension> &,
   const iclass<dimension> &
) {
   return true;
}

// input: recursive
template<class terms, class base, std::size_t dimension, std::size_t n>
inline bool node_coord(
   std::istream &s, metamesh::node<terms,base,dimension> &obj,
   const iclass<n> &
) {
   return
      node_coord(s, obj.value(component<n>()), obj.label(component<n>())) &&
      node_coord(s, obj, iclass<n+1>());
}



// output: base
template<class terms, class base, std::size_t dimension>
inline bool node_coord(
   std::ostream &, const metamesh::node<terms,base,dimension> &,
   const iclass<dimension> &
) {
   return true;
}

// output: recursive
template<class terms, class base, std::size_t dimension, std::size_t n>
inline bool node_coord(
   std::ostream &s, const metamesh::node<terms,base,dimension> &obj,
   const iclass<n> &
) {
   return
      node_coord(
         s << (n ? " " : ""),
         obj.value(component<n>()),
         obj.label(component<n>())
      ) &&
      node_coord(s, obj, iclass<n+1>());
}

}  // internal
}  // metamesh



// =============================================================================
// i/o
// operator>>
// operator<<
// =============================================================================

namespace metamesh {

// istream >> node
template<class terms, class base, std::size_t dimension>
inline std::istream &operator>>(
   std::istream &s,
   metamesh::node<terms,base,dimension> &obj
) {
   // read coordinates, read base, check
   internal::node_coord(s, obj, iclass<0>()) &&
   internal::node_base (s, obj.base()) &&
   internal::node_check(s, obj);
   return s;
}

// ostream << node
template<class terms, class base, std::size_t dimension>
inline std::ostream &operator<<(
   std::ostream &s,
   const metamesh::node<terms,base,dimension> &obj
) {
   // check, write coordinates, write base
   internal::node_check(s, obj) &&
   internal::node_coord(s, obj, iclass<0>()) &&
   internal::node_base (s, obj.base());
   return s;
}

}  // metamesh



// =============================================================================
// operator,
// =============================================================================

// vector<node<terms,base,dimension>> , std::size_t
// non-const
template<class terms, class base, std::size_t dimension>
inline metamesh::node<terms,base,dimension> &operator,(
   std::vector<metamesh::node<terms,base,dimension>> &vec,
   const std::size_t n
) {
   metamesh_assert(n < vec.size());
   return vec[n];
}

// vector<node<terms,base,dimension>> , std::size_t
// const
template<class terms, class base, std::size_t dimension>
inline const metamesh::node<terms,base,dimension> &operator,(
   const std::vector<metamesh::node<terms,base,dimension>> &vec,
   const std::size_t n
) {
   metamesh_assert(n < vec.size());
   return vec[n];
}

#endif
