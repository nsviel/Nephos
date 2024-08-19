#pragma once

#include <Utility/Base/Class/Node.h>

namespace prf{class Node;}
namespace app{class Node;}
namespace io{class Node;}
namespace vk{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace prf::dynamic{class Tasker;}
namespace sys::thread::task{class Pool;}


namespace core{

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

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline dat::Node* get_node_data(){return node_data;}
  inline io::Node* get_node_io(){return node_io;}
  inline eng::Node* get_node_engine(){return node_engine;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline sys::thread::task::Pool* get_thread_pool(){return thread_pool;}
  inline prf::dynamic::Tasker* get_tasker_cpu(){return tasker;}

private:
  vk::Node* node_vulkan;
  io::Node* node_io;
  dat::Node* node_data;
  eng::Node* node_engine;
  prf::Node* node_profiler;
  prf::dynamic::Tasker* tasker;
  sys::thread::task::Pool* thread_pool;
};

}
