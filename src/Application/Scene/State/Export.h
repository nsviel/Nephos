#pragma once

#include <Utility/Namespace.h>
#include <memory>

namespace sce{class Node;}
namespace sce::structure{class Scene;}
namespace sce::structure{class Set;}
namespace dat::gph{class Graph;}
namespace dat::base{class Set;}


namespace sce{

class Export
{
public:
  //Constructor / Destructor
  Export(sce::Node* node_scene);
  ~Export();

public:
  //Main function
  void export_json();

  //Subfunction
  void populate_scene(nlohmann::json& j, std::shared_ptr<dat::base::Set> set);

private:
  dat::gph::Graph* dat_graph;
};

}
