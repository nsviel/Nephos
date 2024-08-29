#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace sys{class Node;}
namespace vk{class Node;}

namespace dat::atr{class Node;}
namespace dat::elm{class Node;}
namespace dat::gph{class Node;}
namespace dat::ply{class Node;}
namespace dat::img{class Node;}


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

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline sys::Node* get_node_system(){return node_system;}

  inline dat::atr::Node* get_node_attribut(){return node_attribut;}
  inline dat::elm::Node* get_node_element(){return node_element;}
  inline dat::gph::Node* get_node_graph(){return node_graph;}
  inline dat::ply::Node* get_node_player(){return node_player;}
  inline dat::img::Node* get_node_image(){return node_image;}

private:
  //Dependancy
  vk::Node* node_vulkan;
  sys::Node* node_system;

  //Child
  dat::atr::Node* node_attribut;
  dat::elm::Node* node_element;
  dat::gph::Node* node_graph;
  dat::ply::Node* node_player;
  dat::img::Node* node_image;
};

}
