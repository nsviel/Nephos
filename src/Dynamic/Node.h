#pragma once

#include <Utility/Base/Class/Node.h>

namespace dyn::proc{class Node;}
namespace sen{class Node;}
namespace core{class Node;}


namespace dyn{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  void loop();
  void gui();
  void reset();

  inline dyn::prc::Node* get_node_processing(){return node_processing;}
  inline sen::Node* get_node_sensor(){return node_sensor;}

private:
  dyn::prc::Node* node_processing;
  sen::Node* node_sensor;
};

}
