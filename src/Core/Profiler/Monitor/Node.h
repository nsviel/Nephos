#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace vk{class Node;}
namespace prf{class Node;}

namespace prf::monitor{class Structure;}
namespace prf::monitor{class Manager;}


namespace prf::monitor{

class Node : public utl::base::Node
{
public:
  Node(prf::Node* node_profiler);
  ~Node();

public:
  //Main function
  void init();
  void loop();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}

  inline prf::monitor::Structure* get_prf_struct(){return prf_struct;}
  inline prf::monitor::Manager* get_prf_monitor(){return prf_monitor;}

private:
  vk::Node* node_vulkan;

  prf::monitor::Structure* prf_struct;
  prf::monitor::Manager* prf_monitor;
};

}
