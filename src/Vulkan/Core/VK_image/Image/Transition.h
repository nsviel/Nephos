#pragma once

#include <vulkan/vulkan.h>

namespace vk::memory{class Allocator;}
namespace vk{class Structure;}
namespace vk::structure{class Transition;}
namespace vk::structure{class Image;}


namespace vk::image{

class Transition
{
public:
  //Constructor / Destructor
  Transition(vk::Structure* vk_struct);
  ~Transition();

public:
  //Main function
  void image_layout_transition(VkCommandBuffer command_buffer, vk::structure::Image& image, VkImageLayout old_layout, VkImageLayout new_layout);
  void image_layout_transition(VkCommandBuffer command_buffer, VkImage image, VkImageLayout old_layout, VkImageLayout new_layout);

  //Subfunction
  VkAccessFlags find_access_flag(VkImageLayout& layout);
  VkPipelineStageFlags find_stage_flag(VkImageLayout& layout);

private:
  vk::Structure* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
};

}