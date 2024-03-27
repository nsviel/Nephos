#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Viewport;}


namespace vk::draw{

class Viewport
{
public:
  Viewport(vk::structure::Vulkan* struct_vulkan);
  ~Viewport();

public:
  //Main function
  void init();
  void cmd_viewport(VkCommandBuffer& command_buffer);
  void update_viewport();

  //Subfunction
  vk::structure::Viewport* create_viewport();

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
