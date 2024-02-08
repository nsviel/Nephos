#pragma once

#include <Utility/Specific/common.h>

namespace vk::command{class Submit;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Object;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Image;}
namespace vk::structure{class Command_buffer;}
namespace vk::command{class Command_buffer;}


namespace vk::command{

class Command
{
public:
  //Constructor / Destructor
  Command(vk::structure::Vulkan* struct_vulkan);
  ~Command();

public:
  //Render pass


  //Image layout transition
  void image_layout_transition(VkCommandBuffer command_buffer, vk::structure::Image* image, VkImageLayout oldLayout, VkImageLayout newLayout);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::command::Submit* vk_submit;
  vk::command::Command_buffer* vk_command_buffer;
};

}
