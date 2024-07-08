#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk{class Structure;}
namespace vk::device::structure{class Physical;}
namespace vk::queue::structure{class Queue;}


namespace vk::device::queue{

class Manager
{
public:
  //Constructor / Destructor
  Manager(vk::Structure* vk_struct);
  ~Manager();

public:
  //Main function
  void create_queue(vk::queue::structure::Queue& queue);
  void create_queue_info(std::vector<VkDeviceQueueCreateInfo>& vec_queue_info);

  //Subfunction
  bool suitability_for_presentation(vk::device::structure::Physical& physical_device);
  bool suitability_for_graphics(vk::device::structure::Physical& physical_device);

private:
  vk::Structure* vk_struct;
};

}
