#pragma once

#include <Utility/Specific/common.h>

namespace vk::command{class Submit;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Object;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Image;}


namespace vk::command{

class Command
{
public:
  //Constructor / Destructor
  Command(vk::structure::Vulkan* struct_vulkan);
  ~Command();

public:
  //Command buffer
  void start_command_buffer_once(VkCommandBuffer& command_buffer);
  void start_command_buffer_primary(VkCommandBuffer command_buffer);
  void start_command_buffer_secondary(vk::structure::Renderpass* renderpass, VkCommandBuffer command_buffer);
  void reset_command_buffer(VkCommandBuffer& command_buffer);
  void stop_command_buffer(VkCommandBuffer command_buffer);
  void allocate_command_buffer_primary(VkCommandBuffer& command_buffer);
  void allocate_command_buffer_secondary(vk::structure::Object* data);
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
  vk::structure::Vulkan* struct_vulkan;
  vk::command::Submit* vk_submit;
};

}
