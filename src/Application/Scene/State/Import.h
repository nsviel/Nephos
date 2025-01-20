#pragma once

#include <Utility/Namespace.h>
#include <memory>

namespace sce{class Node;}
namespace sce::structure{class Scene;}
namespace sce::structure{class Set;}
namespace dat::gph{class Graph;}
namespace dat::base{class Set;}


namespace sce{

class Import
{
public:
  //Constructor / Destructor
  Import(sce::Node* node_scene);
  ~Import();

public:
  //Main function
  void import_json();

private:
  dat::gph::Graph* dat_graph;
};

}
