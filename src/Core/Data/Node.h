#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace dat::elm{class Node;}
namespace dat::graph{class Node;}


namespace dat{

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

  inline dat::elm::Node* get_node_element(){return node_element;}
  inline dat::graph::Node* get_node_graph(){return node_graph;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;

  //Child
  dat::elm::Node* node_element;
  dat::graph::Node* node_graph;
};

}
