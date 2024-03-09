#pragma once

#include <Vulkan/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Queue{
  //---------------------------

  VkQueue handle;
  float priority = 1.0f;
  int family_ID = -1;
  int family_index = 0;

  vk::pool::Command_buffer command_buffer;

  //---------------------------
};

}

namespace vk::structure::queue{

struct Family{
  //---------------------------

  int ID = -1;
  int current_index = 0;
  int nb_queue = 0;

  bool graphics = 0;
  bool compute = 0;
  bool transfer = 0;
  bool sparseBinding = 0;
  bool presentation = 0;

  VkQueueFamilyProperties property;
  vector<vk::structure::Queue*> vec_queue;

  //---------------------------
};

struct Pool{
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
