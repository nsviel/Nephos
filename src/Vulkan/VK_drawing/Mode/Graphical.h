#pragma once

#include <Vulkan/VK_drawing/Drawer.h>
#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Semaphore;}
namespace vk::structure{class Command;}
namespace vk::structure{class Renderpass;}
namespace vk::memory{class Transfer;}


namespace vk::draw{

class Graphical : public vk::draw::Drawer
{
public:
  //Constructor / Destructor
  Graphical(vk::structure::Vulkan* vk_struct);
  ~Graphical();

public:
  //Main functions
  void draw_frame();

  //Subfunction
  bool acquire_image(vk::structure::Semaphore& semaphore);
  void record_renderpass(vector<vk::structure::Command*>& vec_command, vk::structure::Semaphore& semaphore);
  void copy_to_swapchain(vector<vk::structure::Command*>& vec_command, vk::structure::Semaphore& semaphore);
  void submit_presentation(vector<vk::structure::Command*>& vec_command);
  
private:
  vk::memory::Transfer* vk_transfer;
};

}
