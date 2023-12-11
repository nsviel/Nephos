#include "VK_command.h"

#include <Vulkan/VK_command/VK_submit.h>
#include <Vulkan/VK_struct/Namespace.h>


//Constructor / Destructor
VK_command::VK_command(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_submit = new VK_submit(struct_vulkan);

  //---------------------------
}
VK_command::~VK_command(){}

//Command buffer
void VK_command::start_command_buffer_once(VkCommandBuffer& command_buffer){
  //---------------------------

  VkCommandBufferBeginInfo begin_info{};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  VkResult result = vkBeginCommandBuffer(command_buffer, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  //---------------------------
}
void VK_command::start_command_buffer_primary(VkCommandBuffer command_buffer){
  //---------------------------

  VkCommandBufferBeginInfo begin_info{};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = 0;

  VkResult result = vkBeginCommandBuffer(command_buffer, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  //---------------------------
}
void VK_command::start_command_buffer_secondary(vk::structure::Renderpass* renderpass, VkCommandBuffer command_buffer){
  vk::structure::Framebuffer* frame = renderpass->framebuffer;
  //---------------------------

  // Create a VkCommandBufferInheritanceInfo structure
  VkCommandBufferInheritanceInfo inheritanceInfo = {};
  inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
  inheritanceInfo.pNext = nullptr;
  inheritanceInfo.renderPass = renderpass->renderpass; // The render pass to inherit from
  inheritanceInfo.subpass = 0;       // The subpass to inherit from
  inheritanceInfo.framebuffer = frame->fbo; // The framebuffer to inherit from
  inheritanceInfo.occlusionQueryEnable = VK_FALSE; // Whether to enable occlusion query
  inheritanceInfo.queryFlags = 0; // Query flags (if any)
  inheritanceInfo.pipelineStatistics = 0; // Pipeline statistics (if any)

  // Create a VkCommandBufferBeginInfo structure and set the inheritance info
  VkCommandBufferBeginInfo begin_info = {};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.pNext = nullptr;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT; // Optional flags
  begin_info.pInheritanceInfo = &inheritanceInfo;

  VkResult result = vkBeginCommandBuffer(command_buffer, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  //---------------------------
}
void VK_command::reset_command_buffer(VkCommandBuffer& command_buffer){
  //---------------------------

  vkResetCommandBuffer(command_buffer, 0);

  //---------------------------
}
void VK_command::stop_command_buffer(VkCommandBuffer command_buffer){
  //---------------------------

  VkResult result = vkEndCommandBuffer(command_buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to record command buffer!");
  }

  //---------------------------
}
void VK_command::allocate_command_buffer_primary(VkCommandBuffer& command_buffer){
  //---------------------------

  //Command buffer allocation
  VkCommandBufferAllocateInfo alloc_info{};
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc_info.commandPool = struct_vulkan->pool.command;
  alloc_info.commandBufferCount = 1;
  VkResult result = vkAllocateCommandBuffers(struct_vulkan->device.device, &alloc_info, &command_buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }else{
    struct_vulkan->pool.nb_command_allocated++;
  }

  //---------------------------
}
void VK_command::allocate_command_buffer_secondary(vk::structure::Entity* data){
  //---------------------------

  //Command buffer allocation
  VkCommandBufferAllocateInfo alloc_info{};
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
  alloc_info.commandPool = struct_vulkan->pool.command;
  alloc_info.commandBufferCount = 1;

  VkResult result = vkAllocateCommandBuffers(struct_vulkan->device.device, &alloc_info, &data->command_buffer_secondary);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }else{
    struct_vulkan->pool.nb_command_allocated++;
  }

  //---------------------------
}
void VK_command::clean_command_buffer(VkCommandBuffer& command_buffer){
  //---------------------------

  vkFreeCommandBuffers(struct_vulkan->device.device, struct_vulkan->pool.command, 1, &command_buffer);
  struct_vulkan->pool.nb_command_allocated--;

  //---------------------------
}

//Render pass
void VK_command::start_render_pass(vk::structure::Renderpass* renderpass, VkFramebuffer& fbo, bool with_secondary_cb){
  //---------------------------

  this->reset_command_buffer(renderpass->command_buffer);
  this->start_command_buffer_primary(renderpass->command_buffer);

  std::array<VkClearValue, 2> clear_value{};
  clear_value[0].color = {{
    struct_vulkan->param.background_color.x,
    struct_vulkan->param.background_color.y,
    struct_vulkan->param.background_color.z,
    struct_vulkan->param.background_color.w}};
  clear_value[1].depthStencil = {1.0f, 0};

  VkRenderPassBeginInfo renderpass_info{};
  renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderpass_info.renderPass = renderpass->renderpass;
  renderpass_info.framebuffer = fbo;
  renderpass_info.renderArea.offset = {0, 0};
  renderpass_info.renderArea.extent = struct_vulkan->window.extent;
  renderpass_info.clearValueCount = static_cast<uint32_t>(clear_value.size());
  renderpass_info.pClearValues = clear_value.data();

  VkSubpassContents content;
  if(with_secondary_cb){
    content = VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS;
  }else{
    content = VK_SUBPASS_CONTENTS_INLINE;
  }

  vkCmdBeginRenderPass(renderpass->command_buffer, &renderpass_info, content);

  //---------------------------
}
void VK_command::stop_render_pass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vkCmdEndRenderPass(renderpass->command_buffer);

  this->stop_command_buffer(renderpass->command_buffer);

  //---------------------------
}

//Image layout transition
void VK_command::image_layout_transition_single(vk::structure::Image* image, VkImageLayout old_layout, VkImageLayout new_layout){
  //---------------------------

  VkCommandBuffer command_buffer = singletime_command_begin();
  this->image_layout_transition(command_buffer, image, old_layout, new_layout);
  this->singletime_command_end(command_buffer);

  //---------------------------
}
void VK_command::image_layout_transition(VkCommandBuffer command_buffer, vk::structure::Image* image, VkImageLayout old_layout, VkImageLayout new_layout){
  //---------------------------

  VkImageMemoryBarrier barrier{};
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.oldLayout = old_layout;
  barrier.newLayout = new_layout;
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.image = image->image;
  barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  barrier.subresourceRange.baseMipLevel = 0;
  barrier.subresourceRange.levelCount = image->mip_level;
  barrier.subresourceRange.baseArrayLayer = 0;
  barrier.subresourceRange.layerCount = 1;

  VkPipelineStageFlags sourceStage;
  VkPipelineStageFlags destinationStage;
  if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  }
  else if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
  }
  else if (old_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
    barrier.oldLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
    barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
    barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    sourceStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  }
  else if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) {
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

    sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  }else{
    throw std::invalid_argument("unsupported layout transition!");
  }

  vkCmdPipelineBarrier(command_buffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

  //---------------------------
}

//Single time command
VkCommandBuffer VK_command::singletime_command_begin(){
  VkCommandBuffer command_buffer;
  //---------------------------

  this->allocate_command_buffer_primary(command_buffer);
  this->start_command_buffer_once(command_buffer);

  //---------------------------
  return command_buffer;
}
void VK_command::singletime_command_end(VkCommandBuffer command_buffer){
  //---------------------------

  vkEndCommandBuffer(command_buffer);
  vk_submit->submit_command_graphics(command_buffer);
  vkQueueWaitIdle(struct_vulkan->device.queue_graphics);
  this->clean_command_buffer(command_buffer);

  //---------------------------
}
