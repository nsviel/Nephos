#pragma once

#include <Vulkan/Namespace.h>
#include <Utility/Specific/Common.h>


namespace vk::structure{

struct Queue{
  //---------------------------

  VkQueue handle;
  float priority = 1.0f;
  int family_ID = -1;
  int family_index = 0;

  vector<vk::pool::Command_buffer> vec_pool;

  //---------------------------
};

}

namespace vk::structure::queue{

struct Family{
  //---------------------------

  int ID = -1;
  int current_index = 0;
  int nb_queue = 0;

  bool capable_graphics = 0;
  bool capable_compute = 0;
  bool capable_transfer = 0;
  bool capable_sparseBinding = 0;
  bool capable_presentation = 0;

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
