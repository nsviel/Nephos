#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::renderpass{class Renderpass;}
namespace vk::geometry::pipeline::topology{class Triangle;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Render;}
namespace vk::gui{class Imgui;}


namespace vk::gfx::canvas{

class Subpass
{
public:
  //Constructor / Destructor
  Subpass(vk::Structure* vk_struct);
  ~Subpass();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass& renderpass);
  void draw_subpass(std::shared_ptr<vk::structure::Render> render);

private:
  vk::Structure* vk_struct;
  vk::renderpass::Renderpass* vk_renderpass;
  vk::geometry::pipeline::topology::Triangle* vk_triangle;
  vk::gui::Imgui* vk_imgui;
};

}
