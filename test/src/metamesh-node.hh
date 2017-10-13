
// =============================================================================
// ijk
// Sample "base" class
// =============================================================================

// ijk
template<std::size_t dimension>
class ijk { };

// ijk<0>
template<>
struct ijk<0> {
   inline explicit ijk(void) { }

   inline metamesh::diagnostic_t check(const std::string &) const
   {
      return metamesh::diagnostic_good;
   }
};

// ijk<1>
template<>
struct ijk<1> {
   int i;

   inline explicit ijk(void) { }
   inline explicit ijk(const int a)
      : i(a)
   { }

   inline metamesh::diagnostic_t check(const std::string &) const
   {
      return metamesh::diagnostic_good;
   }
};

// ijk<2>
template<>
struct ijk<2> {
   int i, j;

   inline explicit ijk(void) { }
   inline explicit ijk(const int a, const int b)
      : i(a), j(b)
   { }

   inline metamesh::diagnostic_t check(const std::string &) const
   {
      return metamesh::diagnostic_good;
   }
};

// ijk<3>
template<>
struct ijk<3> {
   int i, j, k;

   inline explicit ijk(void) { }
   inline explicit ijk(const int a, const int b, const int c)
      : i(a), j(b), k(c)
   { }

   inline metamesh::diagnostic_t check(const std::string &) const
   {
      return metamesh::diagnostic_good;
   }
};

// node's i/o needs i/o for base (but not for terms); so define them

// ijk<0>
inline std::istream &operator>>(std::istream &s, ijk<0> &)
   { return s; }
inline std::ostream &operator<<(std::ostream &s, const ijk<0> &)
   { return s; }

// ijk<1>
inline std::istream &operator>>(std::istream &s, ijk<1> &obj)
   { return s >> obj.i; }
inline std::ostream &operator<<(std::ostream &s, const ijk<1> &obj)
   { return s << obj.i; }

// ijk<2>
inline std::istream &operator>>(std::istream &s, ijk<2> &obj)
   { return s >> obj.i >> obj.j; }
inline std::ostream &operator<<(std::ostream &s, const ijk<2> &obj)
   { return s << obj.i << ' ' << obj.j; }

// ijk<3>
inline std::istream &operator>>(std::istream &s, ijk<3> &obj)
   { return s >> obj.i >> obj.j >> obj.k; }
inline std::ostream &operator<<(std::ostream &s, const ijk<3> &obj)
   { return s << obj.i << ' ' << obj.j << ' ' << obj.k; }
