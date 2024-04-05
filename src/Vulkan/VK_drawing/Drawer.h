#pragma once

#include <Utility/Specific/Common.h>

namespace vk::draw{class Renderer;}
namespace vk::synchro{class Fence;}
namespace vk::synchro{class Semaphore;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Object;}


namespace vk::draw{

class Drawer
{
public:
  //Constructor / Destructor
  Drawer(vk::structure::Vulkan* vk_struct);
  ~Drawer();

public:
  //Main functions
  virtual void draw_frame(){}

  //Draw command
  void cmd_draw_data(VkCommandBuffer& command_buffer, vk::structure::Object* data);
  void cmd_line_with(VkCommandBuffer& command_buffer, vk::structure::Object* data);

protected:
  vk::structure::Vulkan* vk_struct;
  vk::draw::Renderer* vk_render;
  vk::synchro::Fence* vk_fence;
  vk::synchro::Semaphore* vk_semaphore;
};

}
