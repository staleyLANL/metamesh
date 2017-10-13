
// =============================================================================
// flow
// Sample "base" class
// =============================================================================

// flow
template<std::size_t dimension>
class flow { };

// flow<0>
template<>
struct flow<0> {
   inline explicit flow(void) { }

   inline metamesh::diagnostic_t check(const std::string &) const
   {
      return metamesh::diagnostic_good;
   }
};

// flow<1>
template<>
struct flow<1> {
   float fx;

   inline explicit flow(void) { }
   inline explicit flow(const float a)
      : fx(a)
   { }

   inline metamesh::diagnostic_t check(const std::string &) const
   {
      return metamesh::diagnostic_good;
   }
};

// flow<2>
template<>
struct flow<2> {
   float fx, fy;

   inline explicit flow(void) { }
   inline explicit flow(const float a, const float b)
      : fx(a), fy(b)
   { }

   inline metamesh::diagnostic_t check(const std::string &) const
   {
      return metamesh::diagnostic_good;
   }
};

// flow<3>
template<>
struct flow<3> {
   float fx, fy, fz;

   inline explicit flow(void) { }
   inline explicit flow(const float a, const float b, const float c)
      : fx(a), fy(b), fz(c)
   { }

   inline metamesh::diagnostic_t check(const std::string &) const
   {
      return metamesh::diagnostic_good;
   }
};

// node's i/o needs i/o for base (but not for terms); so defined them

// flow<0>
inline std::istream &operator>>(std::istream &s, flow<0> &)
   { return s; }
inline std::ostream &operator<<(std::ostream &s, const flow<0> &)
   { return s; }

// flow<1>
inline std::istream &operator>>(std::istream &s, flow<1> &obj)
   { return s >> obj.fx; }
inline std::ostream &operator<<(std::ostream &s, const flow<1> &obj)
   { return s << obj.fx; }

// flow<2>
inline std::istream &operator>>(std::istream &s, flow<2> &obj)
   { return s >> obj.fx >> obj.fy; }
inline std::ostream &operator<<(std::ostream &s, const flow<2> &obj)
   { return s << obj.fx << ' ' << obj.fy; }

// flow<3>
inline std::istream &operator>>(std::istream &s, flow<3> &obj)
   { return s >> obj.fx >> obj.fy >> obj.fz; }
inline std::ostream &operator<<(std::ostream &s, const flow<3> &obj)
   { return s << obj.fx << ' ' << obj.fy << ' ' << obj.fz; }



/*
// =============================================================================
// flow
// =============================================================================

class flow {
public:

   // data
   float fx;
   float fy;

   // constructors
   explicit inline flow(void) { }
   explicit inline flow(const float &a, const float &b) : fx(a), fy(b) { }

   // check
   inline metamesh::diagnostic_t check(const std::string &) const
   {
      return metamesh::diagnostic_good;
   }
};

// flow: operator>>
inline std::istream &operator>>(std::istream &s, flow &obj)
{
   return s >> obj.fx >> obj.fy;
}

// flow: operator<<
inline std::ostream &operator<<(std::ostream &s, const flow &obj)
{
   return s << obj.fx << ' ' << obj.fy;
}
*/
