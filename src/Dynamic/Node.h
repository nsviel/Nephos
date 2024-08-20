#pragma once

#include <Utility/Base/Class/Node.h>

namespace app{class Node;}
namespace core{class Node;}
namespace mod{class Node;}

namespace dyn::prc{class Node;}
namespace dyn::sen{class Node;}


namespace dyn{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(app::Node* node_app);
  ~Node();

public:
  void init();
  void loop();
  void clean();

  inline core::Node* get_node_core(){return node_core;}
  inline mod::Node* get_node_module(){return node_module;}

  inline dyn::prc::Node* get_node_processing(){return node_processing;}
  inline dyn::sen::Node* get_node_sensor(){return node_sensor;}

private:
  core::Node* node_core;
  mod::Node* node_module;

  dyn::prc::Node* node_processing;
  dyn::sen::Node* node_sensor;
};

}
