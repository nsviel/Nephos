#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Physical_device;}
namespace vk::queue::structure{class Queue;}


namespace vk::device{

class Queue
{
public:
  //Constructor / Destructor
  Queue(vk::structure::Vulkan* vk_struct);
  ~Queue();

public:
  //Queue family
  void find_queue_family_composition(vk::structure::Physical_device& physical_device);
  void find_queue_family_assigment();

  //Queue object
  void create_queue(vk::queue::structure::Queue& queue);
  void create_queue_info(std::vector<VkDeviceQueueCreateInfo>& vec_queue_info);

  //Subfunction
  bool suitability_for_presentation(vk::structure::Physical_device& physical_device);
  bool suitability_for_graphics(vk::structure::Physical_device& physical_device);

private:
  vk::structure::Vulkan* vk_struct;
};

}
