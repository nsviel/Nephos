#pragma once

#include <Vulkan/Core/VK_queue/Structure/Queue.h>
#include <vulkan/vulkan.h>


namespace vk::structure{

struct Queue_family{
  //---------------------------

  int ID = -1;
  int current_index = 0;
  int nb_queue = 0;

  bool capable_graphics = 0;
  bool capable_compute = 0;
  bool capable_transfer = 0;
  bool capable_sparseBinding = 0;
  bool capable_presentation = 0;

  VkQueueFamilyProperties property = {};
  std::vector<vk::structure::Queue*> vec_queue;
  std::vector<float> vec_priority;

  //---------------------------
};

}
