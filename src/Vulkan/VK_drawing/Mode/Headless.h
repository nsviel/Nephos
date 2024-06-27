#pragma once

#include <Vulkan/VK_drawing/Drawing/Drawer.h>

namespace vk{class Structure;}


namespace vk::draw{

class Headless : public vk::draw::Drawer
{
public:
  //Constructor / Destructor
  Headless(vk::Structure* vk_struct);
  ~Headless();

public:
  //Main function
  void draw_frame();

private:
};

}
