/* -*- C++ -*- */

#ifndef METAMESH_BASIC
#define METAMESH_BASIC

// This file provides miscellaneous basic constructs.



// =============================================================================
// Macros
// =============================================================================

// metamesh_assert
// For debugging
#ifdef METAMESH_ASSERT
#  define metamesh_assert(arg) assert(arg)
#else
#  define metamesh_assert(arg)
#endif



// metamesh_make_global
// For internal use
#define metamesh_make_global(type, name, initial_value)\
   namespace internal {\
      inline type &name ## _function(void) {\
         using  _type = type;\
         static _type value = _type(initial_value);\
         return value;\
      }\
   }\
   namespace { type &name = internal::name ## _function(); }



// =============================================================================
// Constants, types, enums, and miscellaneous small classes
// =============================================================================

namespace metamesh {

// quad
// Shorthand for long double
using quad = long double;

// version
// Metamesh version
namespace { const std::string version = "0.01"; }

// stub
// Defined later
class stub;



namespace {

// pi
const quad pi =
3.1415926535897932384626433832795028841971693993751058209749445923078164062862L;

// twopi (2*pi)
const quad twopi =
6.2831853071795864769252867665590057683943387987502116419498891846156328125724L;

// deg2rad
// rad2deg
// Degree vs. radian multipliers
const quad deg2rad = pi/180.0L;
const quad rad2deg = 180.0L/pi;

}


// default_real_t: Default floating-point type
// default_base_t: Default "base" class from which to derive certain classes
// Note: the "floating-point" type need not necessarily be floating-point
using default_real_t = double;
using default_base_t = stub;


// diagnostic_t
// Diagnostic-related statuses
enum diagnostic_t {
   diagnostic_error   = 0,  // definite problem
   diagnostic_warning = 1,  // likely problem
   diagnostic_note    = 2,  // for-your-information
   diagnostic_good    = 3   // everything is fine
};

}  // metamesh



// =============================================================================
// sametype
// =============================================================================

namespace metamesh {
namespace internal {

// generic
template<class A, class B>
class sametype {
};

// <T,T>
template<class T>
class sametype<T,T> {
public:
   using type =  T;
};

}  // internal
}  // metamesh



// =============================================================================
// Miscellaneous small functions
// =============================================================================

namespace metamesh {
namespace op {

// half
template<class T>
inline T half(const T &val)
{
   return T(0.5)*val;
}


// twice
template<class T>
inline T twice(const T &val)
{
   return val + val;
}


// square
template<class T>
inline T square(const T &val)
{
   return val * val;
}


// clip
template<class T>
inline T clip(const T &one, const T &value, const T &two)
{
   const T min = std::min(one,two);
   const T max = std::max(one,two);
   return value < min ? min : max < value ? max : value;
}

}  // op
}  // metamesh



// =============================================================================
// Multi-argument min and max
// =============================================================================

namespace metamesh {

// min
template<class T>
inline T min(const T &a)
   { return a; }

template<class T>
inline T min(const T &a, const T &b)
   { return std::min(a,b); }

template<class T>
inline T min(const T &a, const T &b, const T &c)
   { return min(a,min(b,c)); }

template<class T>
inline T min(const T &a, const T &b, const T &c, const T &d)
   { return min(a,min(b,c,d)); }

template<class T>
inline T min(const T &a, const T &b, const T &c, const T &d, const T &e)
   { return min(a,min(b,c,d,e)); }



// max
template<class T>
inline T max(const T &a)
   { return a; }

template<class T>
inline T max(const T &a, const T &b)
   { return std::max(a,b); }

template<class T>
inline T max(const T &a, const T &b, const T &c)
   { return max(a,max(b,c)); }

template<class T>
inline T max(const T &a, const T &b, const T &c, const T &d)
   { return max(a,max(b,c,d)); }

template<class T>
inline T max(const T &a, const T &b, const T &c, const T &d, const T &e)
   { return max(a,max(b,c,d,e)); }

}  // metamesh



// =============================================================================
// For diagnostics: flags
// =============================================================================

namespace metamesh {

// notes, warnings, addenda
metamesh_make_global(bool, notes,    true)  // by default, print notes
metamesh_make_global(bool, warnings, true)  // by default, print warnings
metamesh_make_global(bool, addenda,  true)  // by default, print addenda

// warning()
// Forward declaration, because we'll call it in errors_class below
template<class MESSAGE, class CONTEXT>
inline diagnostic_t warning(const MESSAGE &, const CONTEXT &);



// errors
// Is of a class that prohibits it from being set to false
namespace internal {
   class errors_class {
   public:
      inline explicit errors_class(const bool b) { *this = b; }

      // intentional: const assignment operator
      inline const bool &operator=(const bool b) const
      {
         if (!b) {
            const bool warn = metamesh::warnings;
            metamesh::warnings = true;  // back up
            warning("Assignment metamesh::errors = false ignored;\n   "
                    "you can't turn off errors (or this warning)", "");
            metamesh::warnings = warn;  // restore
         }
         static const bool value = true;
         return value;
      }

      // convert to bool
      inline operator bool(void) const { return true; }
   };
}

metamesh_make_global(const internal::errors_class, errors, true)



// diagnostics
// One-stop assignment of notes, warnings, and addenda (but not errors)
namespace internal {
   class diagnostics_class {
   public:
      inline explicit diagnostics_class(const bool b) { *this = b; }

      inline diagnostics_class &operator=(const bool b)
      {
         metamesh::notes    = b;
         metamesh::warnings = b;
         metamesh::addenda  = b;
         return *this;
      }
   };
}  // internal

metamesh_make_global(internal::diagnostics_class, diagnostics, true)



namespace internal {

// ostream << diagnostics_class
inline std::ostream &operator<<(
   std::ostream &s, const metamesh::internal::diagnostics_class &
) {
   return
      s << '('
        << metamesh::notes    << ','
        << metamesh::warnings << ','
        << metamesh::errors   << ','
        << metamesh::addenda  << ')';
}

}  // internal

}  // metamesh



// =============================================================================
// For diagnostics: cerr
// =============================================================================

namespace metamesh {

// cerr
namespace internal {
   class cerr_class {
      std::ostream *ptr;
   public:
      // construct from ostream
      inline explicit cerr_class(std::ostream &s) : ptr(&s) { }

      // assign from ostream
      inline cerr_class &operator=(std::ostream &s)
         { return ptr = &s, *this; }

      // convert to ostream
      inline std::ostream &ostream(void) const
         { return *ptr; }
   };
}  // internal

metamesh_make_global(internal::cerr_class, cerr, std::cerr)



namespace internal {

// cerr << T
template<class T>
inline std::ostream &operator<<(
   metamesh::internal::cerr_class &s,
   const T &obj
) {
   return s.ostream() << obj;
}

inline std::ostream &operator<<(
   metamesh::internal::cerr_class &s,
   std::ostream &(*const fun)(std::ostream &)
) {
   return s.ostream() << fun;
}

}  // internal

}  // metamesh



// =============================================================================
// For diagnostics: functions
// =============================================================================

namespace metamesh {

// new_context
// For internal use
//
// This "context" business relates to printing a diagnostic message's context
// along with the diagnostic itself - giving, say, a warning like this:
//
//    Warning: Something is funny here. Funny strange, not funny funny.
//    It happened in such-and-such context.
//    Which is within this next older context.
//    Which is, finally, within this oldest, outermost context.
//
namespace internal {
   inline std::string new_context(
      const std::string &newcon,  // new/inner
      const std::string &oldcon   // outer/existing
   ) {
      return newcon + (oldcon == "" ? "" : ".\n   ") + oldcon;
   }
}  // internal

// tostring
// For internal use
namespace internal {
   inline std::string tostring(const char *const s)
      { return s ? s : ""; }

   inline std::string tostring(const std::string &str)
      { return str; }

   inline std::string tostring(const std::ostringstream &oss)
      { return oss.str(); }
}  // internal



// addendum
template<class T>
inline void addendum(const T &s)
{
   if (metamesh::addenda) {
      const std::string str = internal::tostring(s);
      if (str.size())
         metamesh::cerr << "   " << str << '.' << std::endl;
   }
}

// diag
// For internal use
namespace internal {
   template<class MESSAGE, class CONTEXT>
   inline diagnostic_t diag(
      const std::string &label, const diagnostic_t value,
      const MESSAGE &message, const CONTEXT &context
   ) {
      metamesh::cerr
         << "[metamesh] " << label << "\n   "
         << tostring(message) << '.' << std::endl;
      metamesh::addendum(context);
      return value;
   }
}  // internal



// note
template<class MESSAGE, class CONTEXT>
inline diagnostic_t note(const MESSAGE &message, const CONTEXT &context)
{
   return metamesh::notes
      ? internal::diag("Note", diagnostic_note, message, context)
      : diagnostic_good;
}

// warning
template<class MESSAGE, class CONTEXT>
inline diagnostic_t warning(const MESSAGE &message, const CONTEXT &context)
{
   return metamesh::warnings
      ? internal::diag("Warning", diagnostic_warning, message, context)
      : diagnostic_good;
}

// error
template<class MESSAGE, class CONTEXT>
inline diagnostic_t error(const MESSAGE &message, const CONTEXT &context)
{
   return internal::diag("ERROR", diagnostic_error, message, context);
}

}  // metamesh



// =============================================================================
// compare_floating
// check_floating
// For internal use
// =============================================================================

namespace metamesh {
namespace internal {

// compare_floating
template<class T>
bool compare_floating(const T &_a, const T &_b)
{
   if (sizeof(T) == sizeof(unsigned)) {
      // sometimes true of float
      const unsigned *const a = (const unsigned *)&_a;
      const unsigned *const b = (const unsigned *)&_b;
      return a[0] == b[0];

   } else if (sizeof(T) == sizeof(unsigned long)) {
      // sometimes true of double
      const unsigned long *const a = (const unsigned long *)&_a;
      const unsigned long *const b = (const unsigned long *)&_b;
      return a[0] == b[0];

   } else if (sizeof(T) == op::twice(sizeof(unsigned long))) {
      // sometimes true of quad
      const unsigned long *const a = (const unsigned long *)&_a;
      const unsigned long *const b = (const unsigned long *)&_b;
      return a[0] == b[0] && a[1] == b[1];

   } else {
      // character-wise fallback
      const unsigned char *const a = (const unsigned char *)&_a;
      const unsigned char *const b = (const unsigned char *)&_b;

      for (std::size_t i = 0;  i < sizeof(T);  ++i)
         if (a[i] != b[i]) return false;
      return true;
   }
}



// check_floating
template<class T>
diagnostic_t check_floating(const T &value, const std::string &context)
{
   diagnostic_t rv = diagnostic_good;  // so far

   // ------------------------
   // Check for infinities
   // ------------------------

   if (std::numeric_limits<T>::has_infinity) {
      // +infinity
      if (compare_floating(std::numeric_limits<T>::infinity(), value))
         rv = error("value is +infinity :-(", context);

      // -infinity
      if (compare_floating(std::numeric_limits<T>::infinity(),-value))
         rv = error("value is -infinity :-(", context);
   }

   // ------------------------
   // Check for NaNs
   // ------------------------

   // quiet NaN
   if (std::numeric_limits<T>::has_quiet_NaN &&
       compare_floating(std::numeric_limits<T>::quiet_NaN(), value))
      rv = error("value is a quiet NaN :-(", context);

   // signaling NaN
   if (std::numeric_limits<T>::has_signaling_NaN &&
       compare_floating(std::numeric_limits<T>::signaling_NaN(), value))
      rv = error("value is a signaling NaN :-(", context);

   return rv;
}

}  // internal
}  // metamesh



// =============================================================================
// stub
// =============================================================================

namespace metamesh {

// stub
class stub {
public:
   // constructor: default
   inline explicit stub(void) { }

   // check
   inline diagnostic_t check(const std::string & = "") const
      { return diagnostic_good; }
};



// istream >> stub
// ostream << stub
inline std::istream &operator>>(std::istream &s, const metamesh::stub &)
   { return s; }
inline std::ostream &operator<<(std::ostream &s, const metamesh::stub &)
   { return s; }

}  // metamesh



// =============================================================================
// print
// Key
// key
// find
// =============================================================================

namespace metamesh {

// print
// For debugging use
inline void print(void)
   { std::cout << std::endl; }

inline void print(const bool &value)
   { std::cout << (value ? "true" : "false") << std::endl; }

inline void print(const unsigned char &value)
   { std::cout << unsigned(value) << std::endl; }

inline void print(const internal::errors_class &value)
   { print(bool(value)); }

inline void print(const internal::diagnostics_class &)
{
   std::cout
      << '('
      << (metamesh::notes    ? "true" : "false") << ','
      << (metamesh::warnings ? "true" : "false") << ','
      << (metamesh::errors   ? "true" : "false") << ','
      << (metamesh::addenda  ? "true" : "false") << ')'
      << std::endl;
}

template<class T>
inline void print(const T &value)
   { std::cout << value << std::endl; }



// Key (forced)
inline void Key(void)
{
   std::cout << "Press <enter> to continue...";
   char ch;
   std::cin.get(ch);
}

// key (conditional)
inline void key(void)
{
#ifndef METAMESH_NO_KEY
   Key();
#endif
}



// find
// Is value in vector?
template<class T, class VALUE>
inline bool find(const std::vector<T> &vec, const VALUE &value)
{
   return std::find(vec.begin(), vec.end(), value) != vec.end();
}

}  // metamesh



// =============================================================================
// loop
// =============================================================================

namespace metamesh {

// get_size: helper class
namespace internal {
   template<class FROM, bool is_integer>
   class get_size { };  // default has nothing

   // with is_integer == true
   template<class FROM>
   class get_size<FROM,true> {
   public:
      // In this case, size() returns its argument, converted to a std::size_t;
      // e.g. if the argument is 1000 (int), size() returns 1000 (std::size_t).
      inline std::size_t operator()(const FROM &from)
         { return std::size_t(from); }
   };

   // with is_integer == false
   template<class FROM>
   class get_size<FROM,false> {
   public:
      // In this case, size() assumes that its argument has its own .size(),
      // as, say, a vector would have; returns that .size() as a std::size_t.
      inline std::size_t operator()(const FROM &from)
         { return std::size_t(from.size()); }
   };
}



/*
--------------------------------------------
   #, left, right    min   end   covers
--------------------------------------------
   0, true,  true    0     0     -
   0, true,  false   0     0     -
   0, false, true    1     0     -
   0, false, false   1     0     -
--------------------------------------------
   1, true,  true    0     1     [0]
   1, true,  false   0     0     -
   1, false, true    1     1     -
   1, false, false   1     0     -
--------------------------------------------
   2, true,  true    0     2     [0..1]
   2, true,  false   0     1     [0]
   2, false, true    1     2     [1]
   2, false, false   1     1     -
--------------------------------------------
   n, true,  true    0     n     [0..n-1]
   n, true,  false   0     n-1   [0..n-2]
   n, false, true    1     n     [1..n-1]
   n, false, false   1     n-1   [1..n-2]
--------------------------------------------
*/

// loop
class loop {

   // data
   std::size_t _min;
   std::size_t _end;  // one past the last, as in the Standard Template Library
   mutable std::size_t current;

   // convert to bool
   // Private. Prevents us from writing "while (i)" instead
   // of "while (i())" for a loop object i.
   inline explicit operator bool(void) const
   {
      assert(false);  // shouldn't get here
      return true;
   }

public:

   // ------------------------
   // Miscellaneous functions
   // ------------------------

   // reset
   inline void reset(void) const { current = _end; }

   // begin, end, min, max
   inline std::size_t begin(void) const { return _min; }  // same as min()
   inline std::size_t end  (void) const { return _end; }
   inline std::size_t min  (void) const { return _min; }  // same as begin()
   inline std::size_t max  (void) const {
      assert(_end > 0);
      return _end-1;
   }  // legit iff _end > 0

   // convert to std::size_t
   inline operator std::size_t(void) const { return current; }


   // ------------------------
   // Constructors
   // ------------------------

   // loop(from, left, right)
   template<class FROM>
   inline explicit loop(
      const FROM &from,
      const bool  left = true, const bool right = true  // "inclusive" of ends
   ) :
     _min(left ? 0 : 1)
   {
      const std::size_t n =
         internal::get_size<FROM,std::numeric_limits<FROM>::is_integer>()(from);
      _end = n ? (right ? n : n-1) : 0;
      reset();
   }

   // loop(from, left, right)
   template<class FROM>
   inline explicit loop(
      const FROM &from, const std::size_t left, const std::size_t right = 0
   ) :
      _min(left)
   {
      const std::size_t n =
         internal::get_size<FROM,std::numeric_limits<FROM>::is_integer>()(from);
      _end = right < n ? n-right : 0;
      reset();
   }

   // loop(from, left, right)
   template<class FROM>
   inline explicit loop(
      const FROM &from, int left, int right = 0
   ) {
      left  = left  < 0 ? -left  : left;
      right = right < 0 ? -right : right;
      _min = std::size_t(left);
      const std::size_t n =
         internal::get_size<FROM,std::numeric_limits<FROM>::is_integer>()(from);
      _end = std::size_t(right) < n ? n-std::size_t(right) : 0;
      reset();
   }


   // ------------------------
   // operator()
   // ------------------------

   // operator()(): forward order
   inline bool operator()(void) const
   {
      if (current < _end)
         current++;
      else
         current = _min;
      return current < _end;
   }

private:

   // operator()(stub): reverse order
   // Stub value is irrelevant; exists only for operator() disambiguation.
   // Decided to make private; use back() or less() (see below) instead.
   inline bool operator()(const stub) const
   {
      if (current > _min)
         current--;
      else
         current = _end;
      return current < _end;
   }

public:

   // ----------------------------
   // User preference, perhaps...
   //    fore(), more()
   //    back(), less()
   // ----------------------------

   inline bool fore(void) const { return (*this)(); }
   inline bool more(void) const { return (*this)(); }

   inline bool back(void) const { return (*this)(stub()); }
   inline bool less(void) const { return (*this)(stub()); }
};



// ostream << loop
inline std::ostream &operator<<(std::ostream &s, const metamesh::loop &loop)
{
   return s << std::size_t(loop);
}

}  // metamesh

#endif
