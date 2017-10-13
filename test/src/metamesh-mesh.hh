
#define prs(value)\
   std::cout << "sizeof(" #value ") = " << sizeof(value) << std::endl;



// =============================================================================
// info
// =============================================================================

class info {
public:
   double hello;
   double world;

   inline explicit info(void) { }
   inline explicit info(const double a, const double b)
      : hello(a), world(b)
   { }

   inline metamesh::diagnostic_t check(const std::string &) const
   {
      return metamesh::diagnostic_good;
   }
};

// operator>>
inline std::istream &operator>>(std::istream &s, info &obj)
{
   return s >> obj.hello >> obj.world;
}

// operator<<
inline std::ostream &operator<<(std::ostream &s, const info &obj)
{
   return s << obj.hello << ' ' << obj.world;
}



// =============================================================================
// mesh types
// =============================================================================

// node
using node0d = metamesh::node<metamesh::cartesian<0>>;
using node1d = metamesh::node<metamesh::cartesian<1>>;
using node2d = metamesh::node<metamesh::cartesian<2>>;
using node3d = metamesh::node<metamesh::cartesian<3>>;

// edge
using edge1d = metamesh::edge<metamesh::two<node1d>>;
using edge2d = metamesh::edge<metamesh::two<node2d>>;
using edge3d = metamesh::edge<metamesh::two<node3d>>;

// face
using face2d = metamesh::face<metamesh::three<edge2d>>;
using face3d = metamesh::face<metamesh::three<edge3d>>;

// cell
using cell3d = metamesh::cell<metamesh::four<face3d>>;



// mesh: 0-form
using mesh0f0d = metamesh::mesh<node0d, info>;
using mesh0f1d = metamesh::mesh<node1d, info>;
using mesh0f2d = metamesh::mesh<node2d, info>;
using mesh0f3d = metamesh::mesh<node3d, info>;

// mesh: 1-form
using mesh1f1d = metamesh::mesh<node1d,edge1d, info>;
using mesh1f2d = metamesh::mesh<node2d,edge2d, info>;
using mesh1f3d = metamesh::mesh<node3d,edge3d, info>;

// mesh: 2-form
using mesh2f2d = metamesh::mesh<node2d,edge2d,face2d, info>;
using mesh2f3d = metamesh::mesh<node3d,edge3d,face3d, info>;

// mesh: 3-form
using mesh3f3d = metamesh::mesh<node3d,edge3d,face3d,cell3d, info>;
