#pragma once

#include <Vulkan/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure::queue{

struct ID{
  //---------------------------

  VkQueue graphics;
  VkQueue presentation;
  VkQueue transfer;

  //---------------------------
};

struct Class{
  //---------------------------

  vk::queue::Transfer* transfer;
  vk::queue::Graphics* graphics;
  vk::queue::Presentation* presentation;

  //---------------------------
};

}
