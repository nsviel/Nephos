#pragma once

#include <Utility/Base/Class/Node.h>

namespace app{class Node;}
namespace vk{class Node;}
namespace prf{class Node;}

namespace io{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace sys{class Node;}

namespace thr::task{class Pool;}


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
  void reset();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline dat::Node* get_node_data(){return node_data;}
  inline io::Node* get_node_io(){return node_io;}
  inline eng::Node* get_node_engine(){return node_engine;}
  inline sys::Node* get_node_system(){return node_system;}

  inline thr::task::Pool* get_thread_pool(){return thread_pool;}

private:
  vk::Node* node_vulkan;
  prf::Node* node_profiler;

  io::Node* node_io;
  dat::Node* node_data;
  eng::Node* node_engine;
  sys::Node* node_system;

  thr::task::Pool* thread_pool;
};

}
