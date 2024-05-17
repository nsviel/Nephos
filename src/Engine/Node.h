#pragma once

#include <Utility/Base/Type/Node.h>

namespace app{class Node;}
namespace ldr{class Node;}
namespace vk{class Node;}
namespace cam{class Node;}
namespace rnd{class Node;}
namespace dat{class Node;}
namespace dyn{class Node;}
namespace prf{class Node;}
namespace prf::graph{class Tasker;}
namespace utl::thread{class Pool;}


namespace eng{

class Node : public utl::base::Node
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
  void close();

  inline prf::Node* get_node_profiler(){return node_profiler;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline cam::Node* get_node_camera(){return node_camera;}
  inline dat::Node* get_node_data(){return node_data;}
  inline ldr::Node* get_node_loader(){return node_loader;}
  inline dyn::Node* get_node_dynamic(){return node_dynamic;}
  inline utl::thread::Pool* get_thread_pool(){return thread_pool;}

private:
  vk::Node* node_vulkan;
  ldr::Node* node_loader;
  dat::Node* node_data;
  cam::Node* node_camera;
  rnd::Node* node_render;
  prf::Node* node_profiler;
  dyn::Node* node_dynamic;
  prf::graph::Tasker* tasker_main;
  utl::thread::Pool* thread_pool;
};

}
