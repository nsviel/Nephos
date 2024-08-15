#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace core{class Node;}
namespace dat{class Node;}
namespace dat::gph{class Graph;}
namespace dat::gph{class Selection;}
namespace dat::gph{class Structure;}
namespace dat::gph::gui{class Panel;}


namespace dat::gph{

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

  inline dat::gph::Graph* get_dat_graph(){return dat_graph;}
  inline dat::gph::Selection* get_dat_selection(){return dat_selection;}
  inline dat::gph::Structure* get_dat_struct(){return dat_struct;}

private:
  //Dependancy
  core::Node* node_core;
  vk::Node* node_vulkan;
  dat::Node* node_data;

  //Child
  dat::gph::Structure* dat_struct;
  dat::gph::Graph* dat_graph;
  dat::gph::Selection* dat_selection;
  dat::gph::gui::Panel* gui_graph;
};

}
