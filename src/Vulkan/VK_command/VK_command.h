#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>


class VK_submit;


class VK_command
{
public:
  //Constructor / Destructor
  VK_command(vk::structure::Struct_vulkan* struct_vulkan);
  ~VK_command();

public:
  //Command buffer
  void start_command_buffer_once(VkCommandBuffer& command_buffer);
  void start_command_buffer_primary(VkCommandBuffer command_buffer);
  void start_command_buffer_secondary(vk::structure::Renderpass* renderpass, VkCommandBuffer command_buffer);
  void reset_command_buffer(VkCommandBuffer& command_buffer);
  void stop_command_buffer(VkCommandBuffer command_buffer);
  void allocate_command_buffer_primary(VkCommandBuffer& command_buffer);
  void allocate_command_buffer_secondary(vk::structure::Entity* data);
  void clean_command_buffer(VkCommandBuffer& command_buffer);

  //Render pass
  void start_render_pass(vk::structure::Renderpass* renderpass, VkFramebuffer& fbo, bool with_secondary_cb);
  void stop_render_pass(vk::structure::Renderpass* renderpass);

  //Image layout transition
  void image_layout_transition(VkCommandBuffer command_buffer, vk::structure::Image* image, VkImageLayout oldLayout, VkImageLayout newLayout);
  void image_layout_transition_single(vk::structure::Image* image, VkImageLayout old_layout, VkImageLayout new_layout);

  //Single time command
  VkCommandBuffer singletime_command_begin();
  void singletime_command_end(VkCommandBuffer command_buffer);

private:
  vk::structure::Struct_vulkan* struct_vulkan;
  VK_submit* vk_submit;
};
