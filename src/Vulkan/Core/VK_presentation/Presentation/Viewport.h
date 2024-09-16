#pragma once

#include <vulkan/vulkan.h>

namespace vk{class Structure;}
namespace vk::structure{class Viewport;}


namespace vk::draw{

class Viewport
{
public:
  Viewport(vk::Structure* vk_struct);
  ~Viewport();

public:
  //Main function
  void init();
  void cmd_viewport(VkCommandBuffer& command_buffer);
  void update_viewport();

  //Subfunction
  vk::structure::Viewport* create_viewport();

private:
  vk::Structure* vk_struct;
};

}
