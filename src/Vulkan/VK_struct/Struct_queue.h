#pragma once

#include <Vulkan/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Queue{
  //---------------------------

  VkQueue ID;
  int ID_family = -1;

  //---------------------------
};

}

namespace vk::structure::queue{

struct family{
  //---------------------------

  VkQueueFamilyProperties property;
  int nb_queue = 0;
  bool graphics = 0;
  bool compute = 0;
  bool transfer = 0;
  bool sparseBinding = 0;
  bool presentation = 0;

  //---------------------------
};

struct Handle{
  //---------------------------

  vk::structure::Queue graphics;
  vk::structure::Queue presentation;
  vk::structure::Queue transfer;

  //---------------------------
};

struct Class{
  //---------------------------

  bool standby = false;
  vk::queue::Transfer* transfer;
  vk::queue::Graphics* graphics;
  vk::queue::Presentation* presentation;

  //---------------------------
};

}
