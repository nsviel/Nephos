#ifndef VK_COMMAND_H
#define VK_COMMAND_H

#include "../VK_struct/struct_frame.h"
#include "../VK_struct/struct_data.h"
#include "../VK_struct/struct_renderpass.h"
#include <ELE_specific/common.h>

class Struct_param;
class VK_engine;
class Struct_vulkan;


class VK_command
{
public:
  //Constructor / Destructor
  VK_command(VK_engine* vk_engine);
  ~VK_command();

public:
  //Command buffer
  void start_command_buffer_primary(VkCommandBuffer command_buffer);
  void start_command_buffer_secondary(Struct_renderpass* renderpass, VkCommandBuffer command_buffer);
  void stop_command_buffer(VkCommandBuffer command_buffer);

  //Render pass
  void start_render_pass(Struct_renderpass* renderpass, Frame* frame, bool with_secondary_cb);
  void stop_render_pass(Struct_renderpass* renderpass);

  //Image layout transition
  void image_layout_transition(VkCommandBuffer command_buffer, Struct_image* image, VkImageLayout oldLayout, VkImageLayout newLayout);
  void image_layout_transition_single(Struct_image* image, VkImageLayout old_layout, VkImageLayout new_layout);

  //Single time command
  VkCommandBuffer singletime_command_begin();
  void singletime_command_end(VkCommandBuffer command_buffer);

private:
  Struct_param* struct_param;
  Struct_vulkan* struct_vulkan;
};


#endif
