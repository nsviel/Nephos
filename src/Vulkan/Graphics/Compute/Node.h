#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Structure;}
namespace vk::gfx::compute::dtc{class Pipeline;}


namespace vk::gfx::compute{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(vk::Structure* vk_struct);
  ~Node();

public:
  //Main function
  void init();
  void loop();

private:
  vk::Structure* vk_struct;
  vk::gfx::compute::dtc::Pipeline* vk_dtc;
};

}
