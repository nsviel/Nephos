#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace core{class Node;}
namespace dat{class Node;}
namespace dat::graph{class Graph;}
namespace dat::graph{class Selection;}
namespace dat::graph{class Structure;}
namespace dat::graph::gui{class Panel;}


namespace dat::graph{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dat::Node* node_data);
  ~Node();

public:
  void init();
  void loop();
  void clean();
  void gui();
  void reset();

  inline core::Node* get_node_core(){return node_core;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline dat::Node* get_node_data(){return node_data;}

  inline dat::graph::Graph* get_dat_graph(){return dat_graph;}
  inline dat::graph::Selection* get_dat_selection(){return dat_selection;}
  inline dat::graph::Structure* get_dat_struct(){return dat_struct;}

private:
  //Dependancy
  core::Node* node_core;
  vk::Node* node_vulkan;
  dat::Node* node_data;

  //Child
  dat::graph::Structure* dat_struct;
  dat::graph::Graph* dat_graph;
  dat::graph::Selection* dat_selection;
  dat::graph::gui::Panel* gui_graph;
};

}
