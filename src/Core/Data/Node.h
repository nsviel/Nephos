#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace core{class Node;}

namespace dat::atr{class Node;}
namespace dat::elm{class Node;}
namespace dat::gph{class Node;}
namespace dat::ply{class Node;}


namespace dat{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  void init();
  void loop();
  void clean();
  void gui();
  void reset();

  inline core::Node* get_node_core(){return node_core;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}

  inline dat::atr::Node* get_node_attribut(){return node_attribut;}
  inline dat::elm::Node* get_node_element(){return node_element;}
  inline dat::gph::Node* get_node_graph(){return node_graph;}
  inline dat::ply::Node* get_node_player(){return node_player;}

private:
  //Dependancy
  core::Node* node_core;
  vk::Node* node_vulkan;

  //Child
  dat::atr::Node* node_attribut;
  dat::elm::Node* node_element;
  dat::gph::Node* node_graph;
  dat::ply::Node* node_player;
};

}
