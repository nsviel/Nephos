#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace vk{class Node;}
namespace prf{class Node;}

namespace prf::hardware{class Structure;}
namespace prf::hardware{class Manager;}


namespace prf::hardware{

class Node : public utl::base::Node
{
public:
  Node(prf::Node* node_profiler);
  ~Node();

public:
  //Main function
  void init();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}

  inline prf::hardware::Structure* get_prf_struct(){return prf_struct;}
  inline prf::hardware::Manager* get_prf_manager(){return prf_manager;}

private:
  vk::Node* node_vulkan;

  prf::hardware::Structure* prf_struct;
  prf::hardware::Manager* prf_manager;
};

}
