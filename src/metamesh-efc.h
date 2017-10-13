/* -*- C++ -*- */

// Intentional: no macro guard

// This file is #included by the files for edges, faces, and cells, in each
// case with the following macros defined:
//
//    metamesh_efc:   edge   face   cell
//    metamesh_str:  "edge" "face" "cell"
//
// For convenience elsewhere, these are #undefined at the end of this file.



// =============================================================================
// edge<terms,base,dimension>
// face<terms,base,dimension>
// cell<terms,base,dimension>
// =============================================================================

namespace metamesh {

template<
   #ifdef METAMESH_NO_DEFAULT
   class  _terms,
   class  _base,
   std::size_t _dimension = std::size_t(_terms::basis_t::dimension)
   #else
   class  _terms,
   class  _base = default_base_t,
   std::size_t _dimension = std::size_t(_terms::basis_t::dimension)
   #endif
>
class metamesh_efc :
   public _terms,
   public _base
{
public:
   // dimension
   static const std::size_t dimension = _terms::basis_t::dimension;

   // types
   using value_t =  typename _terms::basis_t::value_t;
   using basis_t =  typename _terms::basis_t;
   using terms_t = _terms;
   using base_t  = _base;

   // label
   static inline const char *label(void) { return metamesh_str; }


   // ------------------------
   // Constructors
   // ------------------------

   // ctor()
   // ctor(terms)
   inline explicit metamesh_efc(
      const terms_t &terms = terms_t()
   ) :
      terms_t(terms)
   { }

   // ctor(base)
   inline explicit metamesh_efc(
      const base_t &base
   ) :
      base_t (base)
   { }

   // ctor(terms,base)
   inline explicit metamesh_efc(
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
   inline metamesh_efc &operator=(const terms_t &from)
      { return terms() = from, *this; }

   inline metamesh_efc &operator=(const base_t  &from)
      { return base () = from, *this; }

   // retrieve terms/base
   inline       terms_t &terms(void)       { return *this; }
   inline const terms_t &terms(void) const { return *this; }
   inline       base_t  &base (void)       { return *this; }
   inline const base_t  &base (void) const { return *this; }


   // ------------------------
   // operator()
   // ------------------------

   template<class CONTAINER>
   inline typename
   internal::sametype<basis_t, typename CONTAINER::value_type>::type &
   operator()(
      CONTAINER &container,
      const std::size_t i
   ) const {
      metamesh_assert( (*this)[i] < container.size() );
      return container[(*this)[i]];
   }

   template<class CONTAINER>
   inline const typename
   internal::sametype<basis_t, typename CONTAINER::value_type>::type &
   operator()(
      const CONTAINER &container,
      const std::size_t i
   ) const {
      metamesh_assert( (*this)[i] < container.size() );
      return container[(*this)[i]];
   }


   // ------------------------
   // check
   // ------------------------

   // check([context])
   inline diagnostic_t check(const std::string &context = "") const
   {
      return base().check(
         internal::new_context(
           "Detected during " metamesh_str ".check's examination of base",
            context
         )
      );
   }

   // check(nbasis[,context])
   diagnostic_t check(
      const std::size_t nbasis,
      const std::string &context = ""
   ) const;
};

// dimension
template<class _terms, class _base, std::size_t _dimension>
const std::size_t metamesh_efc<_terms,_base,_dimension>::dimension;

}  // metamesh



// =============================================================================
// check(nbasis[,context])
// =============================================================================

namespace metamesh {

template<class _terms, class _base, std::size_t dimension>
diagnostic_t metamesh_efc<_terms,_base,dimension>::check(
   const std::size_t nbasis,
   const std::string &context
) const {
   diagnostic_t rv = diagnostic_good;  // so far

   // major = this type's name, minor = terms type's name
   const std::string major_name = label();
   const std::string minor_name = basis_t::label();
   const char *const major = major_name.c_str();
   const char *const minor = minor_name.c_str();

   // if this element contains any nonzero number of indices into whatever it's
   // based on, but the mesh has zero of those bases, then there's a problem
   if (this->size() != 0 && nbasis == 0) {
      std::ostringstream oss;
      oss << major << ".check called with nbasis == 0; "
         "none of its elements can check as valid";
      return error(oss,context);
   }

   // examine each individual index
   const loop i(*this);  // has .size()
   while (i())
      rv = metamesh::min(
         rv,
         internal::check_index(i, (*this)[i], nbasis, major, minor, context)
      );

   // remember, error < warning < note < good
   return metamesh::min(rv, check(context));  // check base, too
}

}  // metamesh



// =============================================================================
// i/o
// =============================================================================

namespace metamesh {

// istream >> edge,face,cell
template<class terms, class base, std::size_t dimension>
std::istream &operator>>(
   std::istream &s,
   metamesh::metamesh_efc<terms,base,dimension> &obj
) {
   const char *const context = "Detected during istream >> " metamesh_str;
   std::size_t npart;  // e.g., number of faces the given cell is based upon

   // read number of parts, if appropriate
   if (obj.has_const_size)
      npart = obj.size();  // known implicitly; not i/o'd
   else if (!(s >> npart)) {
      std::ostringstream oss;
      oss << "Could not read number of "
          <<  terms::basis_t::label() << " values";
      metamesh::error(oss,context);
      obj.clear();
      return s;
   }

   // prepare the object to receive that many parts
   obj.prepare(npart);

   // read parts
   const metamesh::loop p(npart);
   while (p())
      if (!obj.read(s,p,context)) {
         std::ostringstream oss;
         oss << "Could not read " << terms::basis_t::label()
             << " [" << std::size_t(p) << ']';
         metamesh::error(oss,context);
         obj.clear();
         return s;
      }

   // read base
   if (!(s >> obj.base())) {
      metamesh::error("Could not read base", context);
      obj.clear();
      return s;
   }

   // check
   if (obj.check(
      "Detected in " metamesh_str ".check call after istream >> " metamesh_str
   ) == metamesh::diagnostic_error)  // only worry about full errors here
      obj.clear();

   // done
   return s;
}



// ostream << edge,face,cell
template<class terms, class base, std::size_t dimension>
std::ostream &operator<<(
   std::ostream &s,
   const metamesh::metamesh_efc<terms,base,dimension> &obj
) {
   // check
   if (obj.check(
      "Detected in " metamesh_str ".check call before ostream << " metamesh_str
   ) == metamesh::diagnostic_error)  // only worry about full errors here
      return s;

   // bookkeeping
   const char *const context = "Detected during ostream << " metamesh_str;
   const std::size_t npart = obj.size();

   // write number of parts, if not known implicitly
   if (!obj.has_const_size && !(s << npart << (npart ? "   " : ""))) {
      std::ostringstream oss;
      oss << "Could not write number of "
          <<  terms::basis_t::label() << " values";
      metamesh::error(oss,context);
      return s;
   }

   // write parts
   const metamesh::loop p(npart);  bool first = true;
   while (p()) {
      if (!(s << (first ? "" : " ") << obj[p])) {
         std::ostringstream oss;
         oss << "Could not write " << terms::basis_t::label()
             << " [" << std::size_t(p) << ']';
         metamesh::error(oss,context);
         return s;
      }
      first = false;
   }

   // write base
   std::ostringstream buf;
   buf << obj.base();
   if (!buf || (
        buf.str() != "" &&
      !(s << ((npart || !obj.has_const_size) ? "   " : "") << buf.str())))
      metamesh::error("Could not write base", context);

   // done
   return s;
}

}  // metamesh



// =============================================================================
// operator,
// =============================================================================

// vector<element<terms,base,dimension>> , std::size_t
// non-const
template<class terms, class base, std::size_t dimension>
inline metamesh::metamesh_efc<terms,base,dimension> &operator,(
   std::vector<metamesh::metamesh_efc<terms,base,dimension>> &vec,
   const std::size_t n
) {
   metamesh_assert(n < vec.size());
   return vec[n];
}

// vector<element<terms,base,dimension>> , std::size_t
// const
template<class terms, class base, std::size_t dimension>
inline const metamesh::metamesh_efc<terms,base,dimension> &operator,(
   const std::vector<metamesh::metamesh_efc<terms,base,dimension>> &vec,
   const std::size_t n
) {
   metamesh_assert(n < vec.size());
   return vec[n];
}

#undef metamesh_efc
#undef metamesh_str
