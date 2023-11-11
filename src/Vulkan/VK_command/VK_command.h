#ifndef VK_COMMAND_H
#define VK_COMMAND_H

#include <VK_struct/Struct_frame.h>
#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_entity.h>
#include <VK_struct/Struct_renderpass.h>
#include <ELE_specific/common.h>

class Struct_vulkan;
class VK_engine;
class VK_command_buffer;
class VK_submit;


class VK_command
{
public:
  //Constructor / Destructor
  VK_command(Struct_vulkan* struct_vulkan);
  ~VK_command();

public:
  //Command buffer
  void start_command_buffer_once(VkCommandBuffer& command_buffer);
  void start_command_buffer_primary(VkCommandBuffer command_buffer);
  void start_command_buffer_secondary(Struct_renderpass* renderpass, VkCommandBuffer command_buffer);
  void stop_command_buffer(VkCommandBuffer command_buffer);

  //Render pass
  void start_render_pass(Struct_renderpass* renderpass, VkFramebuffer& fbo, bool with_secondary_cb);
  void stop_render_pass(Struct_renderpass* renderpass);

  //Image layout transition
  void image_layout_transition(VkCommandBuffer command_buffer, Struct_image* image, VkImageLayout oldLayout, VkImageLayout newLayout);
  void image_layout_transition_single(Struct_image* image, VkImageLayout old_layout, VkImageLayout new_layout);

  //Single time command
  VkCommandBuffer singletime_command_begin();
  void singletime_command_end(VkCommandBuffer command_buffer);

private:
  Struct_vulkan* struct_vulkan;
  VK_command_buffer* vk_command_buffer;
  //VK_submit* vk_submit;
};


#endif
