#pragma once

#include <memory>

namespace sce{class Node;}
namespace sce::structure{class Scene;}
namespace dat::gph{class Graph;}
namespace dat::base{class Set;}


namespace sce{

class State
{
public:
  //Constructor / Destructor
  State(sce::Node* node_scene);
  ~State();

public:
  //Main function
  void export_json();
  void populate_scene(sce::structure::Scene& sce_struct, std::shared_ptr<dat::base::Set> set);

private:
  dat::gph::Graph* dat_graph;
};

}
