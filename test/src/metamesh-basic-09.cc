
#include "metamesh.h"

// diags: print certain diagnostics-related flags
void diags(void)
{
   // individually
   metamesh::print(metamesh::notes);
   metamesh::print(metamesh::warnings);
   metamesh::print(metamesh::errors);  // maybe want errors_class print()?
   metamesh::print(metamesh::addenda);

   // together: (notes,warnings,errors,addenda)
   metamesh::print(metamesh::diagnostics);
}


// main
int main(void)
{
   // current values
   diags();

   // illustrate setting the values
   metamesh::notes    = false;
   metamesh::warnings = false;
   metamesh::errors   = false;  // should print a warning!
   metamesh::addenda  = false;

   // new values
   diags();

   // diagnostics sets them all (except for errors)
   metamesh::diagnostics = true;
   diags();

   // metamesh::cerr
   metamesh::cerr = std::cerr;
   metamesh::cerr << "metamesh::cerr set to std::cerr" << std::endl;
   metamesh::cerr = std::cout;
   metamesh::cerr << "metamesh::cerr set to std::cout" << std::endl;
}


/*
qqq I'm wondering, again, what the following in basic.hh was about...

inline std::ostream &operator<<(
   metamesh::internal::cerr_class &s,
   std::ostream &(*const fun)(std::ostream &)
) {
   return s.ostream() << fun;
}
*/
