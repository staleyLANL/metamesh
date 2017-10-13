
#include "metamesh.h"
#include "metamesh-mesh.hh"
using metamesh::print;



// =============================================================================
// function object
// =============================================================================

class function_object {
public:

   // ------------------------
   // 0-form to 1-form
   // ------------------------

   inline metamesh_macro_path     (mesh0f0d,mesh1f1d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh0f0d,mesh1f1d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh0f0d,mesh1f1d) const
   { metamesh_macro_node_on_param;  return true;  }
// inline metamesh_macro_edge_on  (mesh0f0d,mesh1f1d) const
// { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh0f0d,mesh1f1d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh0f0d,mesh1f1d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh0f0d,mesh1f1d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh0f0d,mesh1f1d) const
   { metamesh_macro_node2edge_param;              }
// inline metamesh_macro_edge2edge(mesh0f0d,mesh1f1d) const
// { metamesh_macro_edge2edge_param;              }
// inline metamesh_macro_edge2face(mesh0f0d,mesh1f1d) const
// { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh0f0d,mesh1f1d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh0f0d,mesh1f1d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh0f0d,mesh1f2d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh0f0d,mesh1f2d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh0f0d,mesh1f2d) const
   { metamesh_macro_node_on_param;  return true;  }
// inline metamesh_macro_edge_on  (mesh0f0d,mesh1f2d) const
// { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh0f0d,mesh1f2d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh0f0d,mesh1f2d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh0f0d,mesh1f2d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh0f0d,mesh1f2d) const
   { metamesh_macro_node2edge_param;              }
// inline metamesh_macro_edge2edge(mesh0f0d,mesh1f2d) const
// { metamesh_macro_edge2edge_param;              }
// inline metamesh_macro_edge2face(mesh0f0d,mesh1f2d) const
// { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh0f0d,mesh1f2d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh0f0d,mesh1f2d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh0f0d,mesh1f3d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh0f0d,mesh1f3d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh0f0d,mesh1f3d) const
   { metamesh_macro_node_on_param;  return true;  }
// inline metamesh_macro_edge_on  (mesh0f0d,mesh1f3d) const
// { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh0f0d,mesh1f3d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh0f0d,mesh1f3d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh0f0d,mesh1f3d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh0f0d,mesh1f3d) const
   { metamesh_macro_node2edge_param;              }
// inline metamesh_macro_edge2edge(mesh0f0d,mesh1f3d) const
// { metamesh_macro_edge2edge_param;              }
// inline metamesh_macro_edge2face(mesh0f0d,mesh1f3d) const
// { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh0f0d,mesh1f3d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh0f0d,mesh1f3d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh0f1d,mesh1f1d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh0f1d,mesh1f1d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh0f1d,mesh1f1d) const
   { metamesh_macro_node_on_param;  return true;  }
// inline metamesh_macro_edge_on  (mesh0f1d,mesh1f1d) const
// { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh0f1d,mesh1f1d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh0f1d,mesh1f1d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh0f1d,mesh1f1d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh0f1d,mesh1f1d) const
   { metamesh_macro_node2edge_param;              }
// inline metamesh_macro_edge2edge(mesh0f1d,mesh1f1d) const
// { metamesh_macro_edge2edge_param;              }
// inline metamesh_macro_edge2face(mesh0f1d,mesh1f1d) const
// { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh0f1d,mesh1f1d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh0f1d,mesh1f1d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh0f1d,mesh1f2d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh0f1d,mesh1f2d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh0f1d,mesh1f2d) const
   { metamesh_macro_node_on_param;  return true;  }
// inline metamesh_macro_edge_on  (mesh0f1d,mesh1f2d) const
// { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh0f1d,mesh1f2d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh0f1d,mesh1f2d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh0f1d,mesh1f2d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh0f1d,mesh1f2d) const
   { metamesh_macro_node2edge_param;              }
// inline metamesh_macro_edge2edge(mesh0f1d,mesh1f2d) const
// { metamesh_macro_edge2edge_param;              }
// inline metamesh_macro_edge2face(mesh0f1d,mesh1f2d) const
// { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh0f1d,mesh1f2d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh0f1d,mesh1f2d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh0f1d,mesh1f3d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh0f1d,mesh1f3d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh0f1d,mesh1f3d) const
   { metamesh_macro_node_on_param;  return true;  }
// inline metamesh_macro_edge_on  (mesh0f1d,mesh1f3d) const
// { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh0f1d,mesh1f3d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh0f1d,mesh1f3d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh0f1d,mesh1f3d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh0f1d,mesh1f3d) const
   { metamesh_macro_node2edge_param;              }
// inline metamesh_macro_edge2edge(mesh0f1d,mesh1f3d) const
// { metamesh_macro_edge2edge_param;              }
// inline metamesh_macro_edge2face(mesh0f1d,mesh1f3d) const
// { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh0f1d,mesh1f3d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh0f1d,mesh1f3d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh0f2d,mesh1f1d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh0f2d,mesh1f1d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh0f2d,mesh1f1d) const
   { metamesh_macro_node_on_param;  return true;  }
// inline metamesh_macro_edge_on  (mesh0f2d,mesh1f1d) const
// { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh0f2d,mesh1f1d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh0f2d,mesh1f1d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh0f2d,mesh1f1d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh0f2d,mesh1f1d) const
   { metamesh_macro_node2edge_param;              }
// inline metamesh_macro_edge2edge(mesh0f2d,mesh1f1d) const
// { metamesh_macro_edge2edge_param;              }
// inline metamesh_macro_edge2face(mesh0f2d,mesh1f1d) const
// { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh0f2d,mesh1f1d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh0f2d,mesh1f1d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh0f2d,mesh1f2d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh0f2d,mesh1f2d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh0f2d,mesh1f2d) const
   { metamesh_macro_node_on_param;  return true;  }
// inline metamesh_macro_edge_on  (mesh0f2d,mesh1f2d) const
// { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh0f2d,mesh1f2d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh0f2d,mesh1f2d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh0f2d,mesh1f2d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh0f2d,mesh1f2d) const
   { metamesh_macro_node2edge_param;              }
// inline metamesh_macro_edge2edge(mesh0f2d,mesh1f2d) const
// { metamesh_macro_edge2edge_param;              }
// inline metamesh_macro_edge2face(mesh0f2d,mesh1f2d) const
// { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh0f2d,mesh1f2d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh0f2d,mesh1f2d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh0f2d,mesh1f3d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh0f2d,mesh1f3d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh0f2d,mesh1f3d) const
   { metamesh_macro_node_on_param;  return true;  }
// inline metamesh_macro_edge_on  (mesh0f2d,mesh1f3d) const
// { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh0f2d,mesh1f3d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh0f2d,mesh1f3d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh0f2d,mesh1f3d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh0f2d,mesh1f3d) const
   { metamesh_macro_node2edge_param;              }
// inline metamesh_macro_edge2edge(mesh0f2d,mesh1f3d) const
// { metamesh_macro_edge2edge_param;              }
// inline metamesh_macro_edge2face(mesh0f2d,mesh1f3d) const
// { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh0f2d,mesh1f3d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh0f2d,mesh1f3d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh0f3d,mesh1f1d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh0f3d,mesh1f1d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh0f3d,mesh1f1d) const
   { metamesh_macro_node_on_param;  return true;  }
// inline metamesh_macro_edge_on  (mesh0f3d,mesh1f1d) const
// { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh0f3d,mesh1f1d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh0f3d,mesh1f1d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh0f3d,mesh1f1d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh0f3d,mesh1f1d) const
   { metamesh_macro_node2edge_param;              }
// inline metamesh_macro_edge2edge(mesh0f3d,mesh1f1d) const
// { metamesh_macro_edge2edge_param;              }
// inline metamesh_macro_edge2face(mesh0f3d,mesh1f1d) const
// { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh0f3d,mesh1f1d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh0f3d,mesh1f1d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh0f3d,mesh1f2d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh0f3d,mesh1f2d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh0f3d,mesh1f2d) const
   { metamesh_macro_node_on_param;  return true;  }
// inline metamesh_macro_edge_on  (mesh0f3d,mesh1f2d) const
// { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh0f3d,mesh1f2d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh0f3d,mesh1f2d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh0f3d,mesh1f2d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh0f3d,mesh1f2d) const
   { metamesh_macro_node2edge_param;              }
// inline metamesh_macro_edge2edge(mesh0f3d,mesh1f2d) const
// { metamesh_macro_edge2edge_param;              }
// inline metamesh_macro_edge2face(mesh0f3d,mesh1f2d) const
// { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh0f3d,mesh1f2d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh0f3d,mesh1f2d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh0f3d,mesh1f3d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh0f3d,mesh1f3d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh0f3d,mesh1f3d) const
   { metamesh_macro_node_on_param;  return true;  }
// inline metamesh_macro_edge_on  (mesh0f3d,mesh1f3d) const
// { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh0f3d,mesh1f3d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh0f3d,mesh1f3d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh0f3d,mesh1f3d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh0f3d,mesh1f3d) const
   { metamesh_macro_node2edge_param;              }
// inline metamesh_macro_edge2edge(mesh0f3d,mesh1f3d) const
// { metamesh_macro_edge2edge_param;              }
// inline metamesh_macro_edge2face(mesh0f3d,mesh1f3d) const
// { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh0f3d,mesh1f3d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh0f3d,mesh1f3d) const
// { metamesh_macro_face2cell_param;              }



   // ------------------------
   // 1-form to 2-form
   // ------------------------

   inline metamesh_macro_path     (mesh1f1d,mesh2f2d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh1f1d,mesh2f2d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh1f1d,mesh2f2d) const
   { metamesh_macro_node_on_param;  return true;  }
   inline metamesh_macro_edge_on  (mesh1f1d,mesh2f2d) const
   { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh1f1d,mesh2f2d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh1f1d,mesh2f2d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh1f1d,mesh2f2d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh1f1d,mesh2f2d) const
   { metamesh_macro_node2edge_param;              }
   inline metamesh_macro_edge2edge(mesh1f1d,mesh2f2d) const
   { metamesh_macro_edge2edge_param;              }
   inline metamesh_macro_edge2face(mesh1f1d,mesh2f2d) const
   { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh1f1d,mesh2f2d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh1f1d,mesh2f2d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh1f1d,mesh2f3d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh1f1d,mesh2f3d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh1f1d,mesh2f3d) const
   { metamesh_macro_node_on_param;  return true;  }
   inline metamesh_macro_edge_on  (mesh1f1d,mesh2f3d) const
   { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh1f1d,mesh2f3d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh1f1d,mesh2f3d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh1f1d,mesh2f3d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh1f1d,mesh2f3d) const
   { metamesh_macro_node2edge_param;              }
   inline metamesh_macro_edge2edge(mesh1f1d,mesh2f3d) const
   { metamesh_macro_edge2edge_param;              }
   inline metamesh_macro_edge2face(mesh1f1d,mesh2f3d) const
   { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh1f1d,mesh2f3d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh1f1d,mesh2f3d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh1f2d,mesh2f2d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh1f2d,mesh2f2d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh1f2d,mesh2f2d) const
   { metamesh_macro_node_on_param;  return true;  }
   inline metamesh_macro_edge_on  (mesh1f2d,mesh2f2d) const
   { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh1f2d,mesh2f2d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh1f2d,mesh2f2d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh1f2d,mesh2f2d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh1f2d,mesh2f2d) const
   { metamesh_macro_node2edge_param;              }
   inline metamesh_macro_edge2edge(mesh1f2d,mesh2f2d) const
   { metamesh_macro_edge2edge_param;              }
   inline metamesh_macro_edge2face(mesh1f2d,mesh2f2d) const
   { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh1f2d,mesh2f2d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh1f2d,mesh2f2d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh1f2d,mesh2f3d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh1f2d,mesh2f3d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh1f2d,mesh2f3d) const
   { metamesh_macro_node_on_param;  return true;  }
   inline metamesh_macro_edge_on  (mesh1f2d,mesh2f3d) const
   { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh1f2d,mesh2f3d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh1f2d,mesh2f3d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh1f2d,mesh2f3d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh1f2d,mesh2f3d) const
   { metamesh_macro_node2edge_param;              }
   inline metamesh_macro_edge2edge(mesh1f2d,mesh2f3d) const
   { metamesh_macro_edge2edge_param;              }
   inline metamesh_macro_edge2face(mesh1f2d,mesh2f3d) const
   { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh1f2d,mesh2f3d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh1f2d,mesh2f3d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh1f3d,mesh2f2d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh1f3d,mesh2f2d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh1f3d,mesh2f2d) const
   { metamesh_macro_node_on_param;  return true;  }
   inline metamesh_macro_edge_on  (mesh1f3d,mesh2f2d) const
   { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh1f3d,mesh2f2d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh1f3d,mesh2f2d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh1f3d,mesh2f2d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh1f3d,mesh2f2d) const
   { metamesh_macro_node2edge_param;              }
   inline metamesh_macro_edge2edge(mesh1f3d,mesh2f2d) const
   { metamesh_macro_edge2edge_param;              }
   inline metamesh_macro_edge2face(mesh1f3d,mesh2f2d) const
   { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh1f3d,mesh2f2d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh1f3d,mesh2f2d) const
// { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh1f3d,mesh2f3d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh1f3d,mesh2f3d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh1f3d,mesh2f3d) const
   { metamesh_macro_node_on_param;  return true;  }
   inline metamesh_macro_edge_on  (mesh1f3d,mesh2f3d) const
   { metamesh_macro_edge_on_param;  return true;  }
// inline metamesh_macro_face_on  (mesh1f3d,mesh2f3d) const
// { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh1f3d,mesh2f3d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh1f3d,mesh2f3d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh1f3d,mesh2f3d) const
   { metamesh_macro_node2edge_param;              }
   inline metamesh_macro_edge2edge(mesh1f3d,mesh2f3d) const
   { metamesh_macro_edge2edge_param;              }
   inline metamesh_macro_edge2face(mesh1f3d,mesh2f3d) const
   { metamesh_macro_edge2face_param;              }
// inline metamesh_macro_face2face(mesh1f3d,mesh2f3d) const
// { metamesh_macro_face2face_param;              }
// inline metamesh_macro_face2cell(mesh1f3d,mesh2f3d) const
// { metamesh_macro_face2cell_param;              }



   // ------------------------
   // 2-form to 3-form
   // ------------------------

   inline metamesh_macro_path     (mesh2f2d,mesh3f3d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh2f2d,mesh3f3d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh2f2d,mesh3f3d) const
   { metamesh_macro_node_on_param;  return true;  }
   inline metamesh_macro_edge_on  (mesh2f2d,mesh3f3d) const
   { metamesh_macro_edge_on_param;  return true;  }
   inline metamesh_macro_face_on  (mesh2f2d,mesh3f3d) const
   { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh2f2d,mesh3f3d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh2f2d,mesh3f3d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh2f2d,mesh3f3d) const
   { metamesh_macro_node2edge_param;              }
   inline metamesh_macro_edge2edge(mesh2f2d,mesh3f3d) const
   { metamesh_macro_edge2edge_param;              }
   inline metamesh_macro_edge2face(mesh2f2d,mesh3f3d) const
   { metamesh_macro_edge2face_param;              }
   inline metamesh_macro_face2face(mesh2f2d,mesh3f3d) const
   { metamesh_macro_face2face_param;              }
   inline metamesh_macro_face2cell(mesh2f2d,mesh3f3d) const
   { metamesh_macro_face2cell_param;              }

   inline metamesh_macro_path     (mesh2f3d,mesh3f3d) const
   { metamesh_macro_path_param;                   }
   inline metamesh_macro_more     (mesh2f3d,mesh3f3d) const
   { metamesh_macro_more_param;     return false; }
   inline metamesh_macro_node_on  (mesh2f3d,mesh3f3d) const
   { metamesh_macro_node_on_param;  return true;  }
   inline metamesh_macro_edge_on  (mesh2f3d,mesh3f3d) const
   { metamesh_macro_edge_on_param;  return true;  }
   inline metamesh_macro_face_on  (mesh2f3d,mesh3f3d) const
   { metamesh_macro_face_on_param;  return true;  }
   inline metamesh_macro_action   (mesh2f3d,mesh3f3d) const
   { metamesh_macro_action_param;                 }
   inline metamesh_macro_node2node(mesh2f3d,mesh3f3d) const
   { metamesh_macro_node2node_param;              }
   inline metamesh_macro_node2edge(mesh2f3d,mesh3f3d) const
   { metamesh_macro_node2edge_param;              }
   inline metamesh_macro_edge2edge(mesh2f3d,mesh3f3d) const
   { metamesh_macro_edge2edge_param;              }
   inline metamesh_macro_edge2face(mesh2f3d,mesh3f3d) const
   { metamesh_macro_edge2face_param;              }
   inline metamesh_macro_face2face(mesh2f3d,mesh3f3d) const
   { metamesh_macro_face2face_param;              }
   inline metamesh_macro_face2cell(mesh2f3d,mesh3f3d) const
   { metamesh_macro_face2cell_param;              }
};



// =============================================================================
// main
// =============================================================================

int main(void)
{
}
