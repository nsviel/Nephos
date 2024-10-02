#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace vk{class Structure;}


namespace vk::storage{

class Data
{
public:
  //Constructor / Destructor
  Data(vk::Structure* vk_struct);
  ~Data();

public:
  //Main function


private:
  vk::Structure* vk_struct;

};

}
