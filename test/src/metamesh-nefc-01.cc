
#include "metamesh.h"
using metamesh::print;

int main(void)
{
   // qqq
   // Much of the metamesh-nefc.h file consists of functions for helping
   // with meshes and their parts. At this time, I think I'll test it in
   // concert with testing meshes.
}



#ifdef SALDKJFLSKJFGLSKDJGLSFDKJG

template<class basis, class index>
diagnostic_t check_index(
   const std::size_t i,
   const index_to<basis,index> ibasis,
   const std::size_t nbasis,
   const std::string &form_name,
   const std::string &basis_name,
   const std::string &context
);

template<class CONTAINER>
diagnostic_t check_elements(
   const CONTAINER &vec, const std::size_t pos,
   const std::string &label, const std::string &context);
template<class CONTAINER>
diagnostic_t check_elements(
   const CONTAINER &vec, const std::size_t pos,
   const std::string &label, const std::string &context,
   const std::size_t nbasis);

template<class CONTAINER>
bool element_container_read(
   std::istream &s,       CONTAINER &vec,
   const std::string &label, const std::string &context);
template<class CONTAINER>
bool element_container_write(
   std::ostream &s, const CONTAINER &vec,
   const std::string &label, const std::string &context);

template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool read_nefc(
   std::istream &s,       mesh<node_t,edge_t,face_t,cell_t,base_t,0> &obj,
   const std::string &context);
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool read_nefc(
   std::istream &s,       mesh<node_t,edge_t,face_t,cell_t,base_t,1> &obj,
   const std::string &context);
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool read_nefc(
   std::istream &s,       mesh<node_t,edge_t,face_t,cell_t,base_t,2> &obj,
   const std::string &context);
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool read_nefc(
   std::istream &s,       mesh<node_t,edge_t,face_t,cell_t,base_t,3> &obj,
   const std::string &context);

template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool write_nefc(
   std::ostream &s, const mesh<node_t,edge_t,face_t,cell_t,base_t,0> &obj,
   const std::string &context);
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool write_nefc(
   std::ostream &s, const mesh<node_t,edge_t,face_t,cell_t,base_t,1> &obj,
   const std::string &context);
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool write_nefc(
   std::ostream &s, const mesh<node_t,edge_t,face_t,cell_t,base_t,2> &obj,
   const std::string &context);
template<class node_t, class edge_t, class face_t, class cell_t, class base_t>
inline bool write_nefc(
   std::ostream &s, const mesh<node_t,edge_t,face_t,cell_t,base_t,3> &obj,
   const std::string &context);

#endif
