#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace dat::graph{class Graph;}
namespace dat::graph{class UID;}
namespace dat::graph{class Selection;}
namespace dat::graph{class Structure;}
namespace dat::graph::gui{class Panel;}


namespace dat::graph{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void init();
  void loop();
  void clean();
  void gui();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}

  inline dat::graph::Graph* get_dat_graph(){return dat_graph;}
  inline dat::graph::Selection* get_dat_selection(){return dat_selection;}
  inline dat::graph::UID* get_dat_uid(){return dat_uid;}
  inline dat::graph::Structure* get_dat_struct(){return dat_struct;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;

  //Child
  dat::graph::Structure* dat_struct;
  dat::graph::Graph* dat_graph;
  dat::graph::UID* dat_uid;
  dat::graph::Selection* dat_selection;
  dat::graph::gui::Panel* gui_graph;
};

}
