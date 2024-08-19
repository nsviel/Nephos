#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace dat{class Node;}
namespace core{class Node;}
namespace cam{class Node;}
namespace rnd{class Node;}
namespace ctr{class Node;}
namespace eng::trf{class Node;}


namespace eng{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void reset();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline dat::Node* get_node_data(){return node_data;}

  inline cam::Node* get_node_camera(){return node_camera;}
  inline ctr::Node* get_node_control(){return node_control;}

private:
  vk::Node* node_vulkan;
  dat::Node* node_data;

  cam::Node* node_camera;
  rnd::Node* node_renderer;
  ctr::Node* node_control;
  eng::trf::Node* node_transfor;
};

}
