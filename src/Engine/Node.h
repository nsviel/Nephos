#pragma once

#include <Utility/Specific/Common.h>

namespace app{class Node;}
namespace vk{class Node;}
namespace prf{class Node;}
namespace prf::graph{class Tasker;}
namespace cam{class Node;}
namespace eng::scene{class Node;}
namespace eng::capture{class Node;}
namespace eng::module{class Node;}
namespace rnd{class Node;}


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
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline eng::capture::Node* get_node_capture(){return node_capture;}

private:
  prf::Node* node_profiler;
  vk::Node* node_vulkan;

  prf::graph::Tasker* tasker_main;
  cam::Node* node_camera;
  eng::scene::Node* node_scene;
  eng::capture::Node* node_capture;
  eng::module::Node* node_module;
  rnd::Node* node_rendering;
};

}
