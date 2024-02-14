#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Queue{
  //---------------------------

  VkQueue graphics;
  VkQueue presentation;
  VkQueue transfer;

  //---------------------------
};

}
