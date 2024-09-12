#pragma once

namespace vk{class Structure;}
namespace vk::renderpass{class Renderpass;}
namespace vk::render::pipeline{class Canvas;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}
namespace vk::gui{class Imgui;}


namespace vk::render::onscreen{

class Subpass
{
public:
  //Constructor / Destructor
  Subpass(vk::Structure* vk_struct);
  ~Subpass();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass* renderpass);

  //Subfunction
  void draw(vk::structure::Subpass* subpass);

private:
  vk::Structure* vk_struct;
  vk::renderpass::Renderpass* vk_renderpass;
  vk::render::pipeline::Canvas* vk_pipeline;
  vk::gui::Imgui* vk_imgui;
};

}
