#pragma once

#include <Utility/Base/Class/Node.h>

namespace app{class Node;}
namespace io{class Node;}
namespace vk{class Node;}
namespace cam{class Node;}
namespace rnd{class Node;}
namespace dat{class Node;}
namespace dyn{class Node;}
namespace prf{class Node;}
namespace ope{class Node;}
namespace rad{class Node;}
namespace ctl{class Node;}
namespace dat::graph{class Node;}
namespace prf::dynamic{class Tasker;}
namespace utl::thread::task{class Pool;}


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
  inline dat::graph::Node* get_node_graph(){return node_graph;}
  inline io::Node* get_node_io(){return node_io;}
  inline ctl::Node* get_node_control(){return node_control;}
  inline ope::Node* get_node_operation(){return node_operation;}
  inline dyn::Node* get_node_dynamic(){return node_dynamic;}
  inline rad::Node* get_node_radio(){return node_radio;}
  inline utl::thread::task::Pool* get_thread_pool(){return thread_pool;}
  inline prf::dynamic::Tasker* get_tasker_cpu(){return tasker;}

private:
  app::Node* node_app;
  rad::Node* node_radio;
  ope::Node* node_operation;
  vk::Node* node_vulkan = nullptr;
  io::Node* node_io = nullptr;
  dat::Node* node_data = nullptr;
  cam::Node* node_camera = nullptr;
  rnd::Node* node_interface = nullptr;
  prf::Node* node_profiler = nullptr;
  dyn::Node* node_dynamic = nullptr;
  ctl::Node* node_control = nullptr;
  dat::graph::Node* node_graph;
  prf::dynamic::Tasker* tasker;
  utl::thread::task::Pool* thread_pool;
};

}
