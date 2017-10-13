/* -*- C++ -*- */

#ifndef METAMESH
#define METAMESH

// To get metamesh, #include this file.



// =============================================================================
// Re: kip
// =============================================================================

#if defined(KIP) || defined(KIP_RENDERER) || defined(KIP_RAYTRACER)
   #undef  KIP_RENDERER
   #define KIP_RENDERER

   // we have kip, so...
   #define kip_yes          (true)
   #define kip_yes_and(arg) (arg)
   #define kip_yes_but(arg) (arg)
   #define kip_yes_or( arg) (true)
   #define kip_no           (false)
   #define kip_no_and( arg) (false)
   #define kip_no_but( arg) (false)
   #define kip_no_or(  arg) (arg)

#else

   // we don't have kip, so...
   #define kip_yes          (false)
   #define kip_yes_and(arg) (false)
   #define kip_yes_but(arg) (false)
   #define kip_yes_or( arg) (arg)
   #define kip_no           (true)
   #define kip_no_and( arg) (arg)
   #define kip_no_but( arg) (arg)
   #define kip_no_or(  arg) (true)

#endif



// =============================================================================
// Macros: debugging-related
// =============================================================================

// Prevent certain template types from having defaults.
// Normal behavior: those types have defaults.
// #define METAMESH_NO_DEFAULT

// Place asserts in certain places.
// Normal behavior: no such asserts (they'd slow the code).
// #define METAMESH_ASSERT



// =============================================================================
// Includes: general
// =============================================================================

// C++
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

// OpenMP
#ifdef _OPENMP
#include <omp.h>
#endif



// =============================================================================
// Includes: metamesh
// =============================================================================

// ------------------------
// basics
// ------------------------

#include "metamesh-basic.h"
#include "metamesh-rgb.h"
#include "metamesh-color.h"
#include "metamesh-point.h"
#include "metamesh-tuple.h"


// ------------------------
// nodes, edges,
// faces, cells
// ------------------------

// nodes: helper constructs
#include "metamesh-nefc.h"

// nodes
#include "metamesh-coord.h"
#include "metamesh-node.h"

// edges, faces, cells
#include "metamesh-edge.h"
#include "metamesh-face.h"
#include "metamesh-cell.h"


// ------------------------
// meshes
// ------------------------

#include "metamesh-mesh.h"


// ------------------------
// extrusion
// ------------------------

// support
#include "metamesh-support.h"
#include "metamesh-macro.h"
#include "metamesh-plugin.h"
#include "metamesh-more.h"

// 0-form to 1-form
#include "metamesh-extrude01.h"

// 1-form to 2-form
#include "metamesh-extrude12.h"
#include "metamesh-fnode.h"
#include "metamesh-fedge.h"

// 2-form to 3-form
#include "metamesh-extrude23.h"
#include "metamesh-fnode-cnode.h"
#include "metamesh-fnode-cedge.h"
#include "metamesh-fnode-cface.h"
#include "metamesh-fedge-cnode.h"
#include "metamesh-fedge-cedge.h"
#include "metamesh-fedge-cface.h"

// user API
#include "metamesh-extrude.h"


// ------------------------
// images
// ------------------------

#include "metamesh-image.h"


// ------------------------
// kip renderer interface
// ------------------------

// kip not required
#include "metamesh-kip-stream.h"
#include "metamesh-kip-axis.h"
#include "metamesh-kip-misc.h"
#include "metamesh-kip-write.h"

// kip required
#if defined(KIP_RENDERER)
#include "metamesh-kip-scene.h"
#endif

/*
// unfinished
#include "metamesh-kip-window.h"
#include "metamesh-kip-interactive.h"
#include "metamesh-kip-gui.h"
*/



// =============================================================================
// The following nonsense inhibits spurious "defined but not used" warnings
// that some compilers might generate. Essentially, this is done by referring
// to values that metamesh provides to users, so that those values won't be
// reported as unused even if nobody otherwise uses them in a particular code.
// =============================================================================

namespace metamesh {
namespace internal {

inline const char &function(void);
namespace {
   const char &fun = function();  // so that function is used
}
inline const char &function(void)
{
   // so that fun is used
   (void)metamesh::internal::fun;

   // see metamesh-basic.h
#ifdef METAMESH_BASIC
   (void)metamesh::notes;
   (void)metamesh::warnings;
   (void)metamesh::addenda;
   (void)metamesh::diagnostics;
#endif

   // see metamesh-tuple.h
#ifdef METAMESH_TUPLE
   (void)metamesh::tup;
#endif

   /*
qqq I moved these elsewhere; change #ifdef and put back in sometime
   // see metamesh-support.h
#ifdef METAMESH_SUPPORT
   (void)metamesh::epsilon;
   (void)metamesh::assign;
   (void)metamesh::noop;
   (void)metamesh::on;
   (void)metamesh::off;
#endif
   */

   // return value
   static const char c = '\0';
   return c;
}

}  // internal
}  // metamesh

#endif
