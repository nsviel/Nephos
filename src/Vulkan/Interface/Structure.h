#pragma once

#include <Vulkan/Interface/Structure/Parameter.h>
#include <Vulkan/Interface/Structure/State.h>


namespace vk::structure{

struct Interface{
  //---------------------------

  vk::structure::Parameter param;
  vk::structure::State state;

  //---------------------------
};

}
