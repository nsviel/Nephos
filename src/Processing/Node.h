#pragma once

#include <Utility/Base/Class/Node.h>

namespace app{class Node;}
namespace rad{class Node;}
namespace core{class Node;}
namespace k4n{class Node;}
namespace rlx{class Node;}


namespace mod{

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

private:
  core::Node* node_core;
  k4n::Node* node_kinect;
  rlx::Node* node_realsense;
  rad::Node* node_radio;
};

}
