#pragma once

#include <Utility/Specific/Common.h>

namespace app{class Node;}
namespace vk{class Node;}
namespace prf{class Node;}
namespace prf::graph{class Tasker;}
namespace cam{class Node;}
namespace sce{class Node;}
namespace rnd{class Node;}
namespace dat{class Node;}


namespace eng{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(app::Node* node_app);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void clean();
  void reset();

  inline prf::Node* get_node_profiler(){return node_profiler;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline cam::Node* get_node_camera(){return node_camera;}
  inline sce::Node* get_node_scene(){return node_scene;}
  inline dat::Node* get_node_data(){return node_data;}

private:
  prf::Node* node_profiler;
  vk::Node* node_vulkan;

  dat::Node* node_data;
  prf::graph::Tasker* tasker_main;
  cam::Node* node_camera;
  sce::Node* node_scene;

  rnd::Node* node_render;
};

}
