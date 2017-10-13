
#include "metamesh.h"
using metamesh::print;

void fun(void)
{
}

int main(void)
{
   // epsilon
   print(sizeof(metamesh::epsilon));
   print(metamesh::epsilon);
   metamesh::epsilon = 1e-6;
   print(metamesh::epsilon);
   print();

   // get_eps()
   print(metamesh::internal::get_eps<double>());
   metamesh::epsilon = 0;
   print(metamesh::internal::get_eps<float>());
   print(metamesh::internal::get_eps<double>());
   print(metamesh::internal::get_eps<metamesh::quad>());
   print();

   /*
   // assign, noop, on, off
   print((void *)&metamesh::assign != (void*)0);
   print((void *)&metamesh::noop   != (void*)0);
   print((void *)&metamesh::on     != (void*)0);
   print((void *)&metamesh::off    != (void*)0);
   */

   // assign, noop, on, off
   print((const void *)&metamesh::assign != (void *)&fun);
   print((const void *)&metamesh::noop   != (void *)&fun);
   print((const void *)&metamesh::on     != (void *)&fun);
   print((const void *)&metamesh::off    != (void *)&fun);

   // random
   metamesh::random a(0.1);
   metamesh::random b(0.9);
}
