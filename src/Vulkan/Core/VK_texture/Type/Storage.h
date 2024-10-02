#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace vk{class Structure;}


namespace vk::texture{

class Storage
{
public:
  //Constructor / Destructor
  Storage(vk::Structure* vk_struct);
  ~Storage();

public:
  //Main function


private:
  vk::Structure* vk_struct;

};

}
