#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace mod{class Node;}
namespace dyn::prc{class Node;}
namespace sen{class Node;}


namespace dyn{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  void init();
  void loop();
  void gui();
  void reset();
  void clean();

  inline core::Node* get_node_core(){return node_core;}
  inline mod::Node* get_node_module(){return node_module;}

  inline dyn::prc::Node* get_node_processing(){return node_processing;}
  inline sen::Node* get_node_sensor(){return node_sensor;}

private:
  core::Node* node_core;
  mod::Node* node_module;

  dyn::prc::Node* node_processing;
  sen::Node* node_sensor;
};

}
