#pragma once

#include <Utility/Base/Class/Node.h>

namespace rad{class Node;}
namespace prf{class Node;}
namespace core{class Node;}
namespace dat{class Node;}
namespace vk{class Node;}

namespace rad::cal{class Structure;}
namespace rad::cal{class Process;}


namespace rad::cal{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(rad::Node* node_radio);
  ~Node();

public:
  //Main function
  void loop();

  inline core::Node* get_node_core(){return node_core;}
  inline dat::Node* get_node_data(){return node_data;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline rad::cal::Structure* get_rad_struct(){return rad_struct;}
  inline rad::cal::Process* get_rad_process(){return rad_process;}

private:
  //Dependancy
  core::Node* node_core;
  dat::Node* node_data;
  vk::Node* node_vulkan;
  prf::Node* node_profiler;

  //Child
  rad::cal::Structure* rad_struct;
  rad::cal::Process* rad_process;
};

}
