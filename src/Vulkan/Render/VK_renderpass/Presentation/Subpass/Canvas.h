#pragma once

namespace vk{class Structure;}
namespace vk::renderpass{class Renderpass;}
namespace vk::render::pipeline{class Factory;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}
namespace vk::gui{class Imgui;}


namespace vk::present::subpass{

class Canvas
{
public:
  //Constructor / Destructor
  Canvas(vk::Structure* vk_struct);
  ~Canvas();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass& renderpass);
  void draw_subpass(vk::structure::Subpass& subpass);

private:
  vk::Structure* vk_struct;
  vk::renderpass::Renderpass* vk_renderpass;
  vk::render::pipeline::Factory* vk_factory;
  vk::gui::Imgui* vk_imgui;
};

}