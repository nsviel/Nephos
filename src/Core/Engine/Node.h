#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace dyn{class Node;}
namespace dat{class Node;}
namespace prf{class Node;}

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

  inline core::Node* get_node_core(){return node_core;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline dyn::Node* get_node_dynamic(){return node_dynamic;}
  inline dat::Node* get_node_data(){return node_data;}

  inline cam::Node* get_node_camera(){return node_camera;}
  inline ctr::Node* get_node_control(){return node_control;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

private:
  core::Node* node_core;
  vk::Node* node_vulkan;
  dat::Node* node_data;
  dyn::Node* node_dynamic;

  prf::Node* node_profiler;
  cam::Node* node_camera;
  rnd::Node* node_renderer;
  ctr::Node* node_control;
  eng::trf::Node* node_transfor;
};

}
