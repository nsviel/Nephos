#include "Transition.h"

#include <Vulkan/Namespace.h>


namespace vk::memory{

//Constructor / Destructor
Transition::Transition(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);
  this->vk_command = new vk::commandbuffer::Command_buffer(vk_struct);

  //---------------------------
}
Transition::~Transition(){}

//Main function
void Transition::image_layout_transition(vk::structure::Image& image, VkImageLayout old_layout, VkImageLayout new_layout){
  //---------------------------

  //Image transition from undefined layout to read only layout
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = vk_command->query_free_command_buffer(vk_struct->core.device.queue.graphics);
  vk_command->start_command_buffer_primary(*command_buffer);

  //Transition
  this->image_layout_transition(command_buffer->handle, image, old_layout, new_layout);

  //End and submit command
  vk_command->end_command_buffer(*command_buffer);
  vk_command->submit_command_buffer(command_buffer, vk_struct->core.command.graphics);

  //---------------------------
}
void Transition::image_layout_transition(VkCommandBuffer command_buffer, vk::structure::Image& image, VkImageLayout old_layout, VkImageLayout new_layout){
  //---------------------------

  this->image_layout_transition(command_buffer, image.handle, old_layout, new_layout);
  image.layout = new_layout;

  //---------------------------
}
void Transition::image_layout_transition(VkCommandBuffer command_buffer, VkImage image, VkImageLayout old_layout, VkImageLayout new_layout){
  //---------------------------

  VkImageMemoryBarrier barrier{};
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.oldLayout = old_layout;
  barrier.newLayout = new_layout;
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.image = image;
  barrier.srcAccessMask = find_access_flag(old_layout);
  barrier.dstAccessMask = find_access_flag(new_layout);
  barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  barrier.subresourceRange.baseMipLevel = 0;
  barrier.subresourceRange.levelCount = 1;
  barrier.subresourceRange.baseArrayLayer = 0;
  barrier.subresourceRange.layerCount = 1;

  VkPipelineStageFlags stage_src = find_stage_flag(old_layout);
  VkPipelineStageFlags stage_dst = find_stage_flag(new_layout);
  vkCmdPipelineBarrier(command_buffer, stage_src, stage_dst, 0, 0, nullptr, 0, nullptr, 1, &barrier);

  //---------------------------
}

//Subfunction
VkAccessFlags Transition::find_access_flag(VkImageLayout& layout){
  VkAccessFlags flag = 0;
  //---------------------------

  switch(layout){
    case VK_IMAGE_LAYOUT_UNDEFINED:{
      flag = VK_ACCESS_NONE_KHR;
      break;
    }
    case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:{
      flag = VK_ACCESS_TRANSFER_READ_BIT;
      break;
    }
    case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:{
      flag = VK_ACCESS_TRANSFER_WRITE_BIT;
      break;
    }
    case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:{
      flag = VK_ACCESS_SHADER_READ_BIT;
      break;
    }
    case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:{
      flag = VK_ACCESS_NONE_KHR;
      break;
    }
    case VK_IMAGE_LAYOUT_GENERAL:{
      flag = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
      break;
    }
    default:{
      throw std::invalid_argument("[error] unsupported layout transition - access flag");
    }
  }

  //---------------------------
  return flag;
}
VkPipelineStageFlags Transition::find_stage_flag(VkImageLayout& layout){
  VkPipelineStageFlags flag = 0;
  //---------------------------

  switch(layout){
    case VK_IMAGE_LAYOUT_UNDEFINED:{
      flag = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
      break;
    }
    case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
    case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:{
      flag = VK_PIPELINE_STAGE_TRANSFER_BIT;
      break;
    }
    case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:{
      flag = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
      break;
    }
    case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:{
      flag = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
      break;
    }
    case VK_IMAGE_LAYOUT_GENERAL:{
      flag = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;
      break;
    }
    default:{
      throw std::invalid_argument("[error] unsupported layout transition - stage flag");
    }
  }

  //---------------------------
  return flag;
}


}
