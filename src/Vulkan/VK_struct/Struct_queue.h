#pragma once

#include <Vulkan/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Queue{
  //---------------------------

  VkQueue handle;
  float priority = 1.0f;
  int family_ID = -1;
  int family_index = -1;

  //---------------------------
};

}

namespace vk::structure::queue{

struct Family{
  //---------------------------

  int ID = -1;
  VkQueueFamilyProperties property;
  vector<float> vec_queue_priority;
  int nb_queue_required = 0;
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
