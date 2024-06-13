#pragma once

#include <Utility/Specific/Common.h>

namespace vk::main{class Engine;}
namespace vk::gui{class Imgui;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}


namespace vk::render::gui{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::structure::Vulkan* vk_struct);
  ~Renderpass();

public:
  //Main function
  void init_renderpass();
  void create_subpass(vk::structure::Renderpass* renderpass);
  void pipeline_triangle(vk::structure::Subpass* subpass);
  
  //Draw function
  void draw(vk::structure::Subpass* subpass);

private:
  vk::structure::Vulkan* vk_struct;
  vk::main::Engine* vk_engine;
  vk::gui::Imgui* vk_imgui;
};

}
