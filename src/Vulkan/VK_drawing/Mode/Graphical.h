#pragma once

#include <Vulkan/VK_drawing/Drawer.h>
#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}


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

private:
};

}
