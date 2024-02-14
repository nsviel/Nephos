#pragma once

#include <Vulkan/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Queue_object{
  //---------------------------

  VkQueue graphics;
  VkQueue presentation;
  VkQueue transfer;

  //---------------------------
};

struct Queue_class{
  //---------------------------

  vk::queue::Transfer* transfer;
  vk::queue::Graphics* graphics;
  vk::queue::Presentation* presentation;

  //---------------------------
};

}
