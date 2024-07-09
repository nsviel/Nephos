#pragma once

namespace vk{class Structure;}
namespace vk::renderpass{class Renderpass;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}
namespace vk::gui{class Imgui;}


namespace vk::render::gui{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::Structure* vk_struct);
  ~Renderpass();

public:
  //Main function
  void init();

  //Init function
  void create_renderpass(vk::structure::Renderpass* renderpass);
  void create_subpass(vk::structure::Renderpass* renderpass);
  void create_pipeline_triangle(vk::structure::Subpass* subpass);

  //Draw function
  void draw(vk::structure::Subpass* subpass);

private:
  vk::Structure* vk_struct;
  vk::renderpass::Renderpass* vk_renderpass;
  vk::gui::Imgui* vk_imgui;
};

}
