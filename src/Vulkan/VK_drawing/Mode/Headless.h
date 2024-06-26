#pragma once

#include <Vulkan/VK_drawing/Drawer.h>

namespace vk::structure{class Vulkan;}


namespace vk::draw{

class Headless : public vk::draw::Drawer
{
public:
  //Constructor / Destructor
  Headless(vk::structure::Vulkan* vk_struct);
  ~Headless();

public:
  //Main function
  void draw_frame();

private:
};

}
