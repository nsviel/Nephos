#pragma once

#include <Vulkan/VK_drawing/Drawer.h>
#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Semaphore;}
namespace vk::structure{class Command;}
namespace vk::structure{class Renderpass;}


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
  void record_renderpass(vk::structure::Renderpass* renderpass, vk::structure::Semaphore* semaphore, vector<vk::structure::Command*>& vec_command);

private:
};

}
