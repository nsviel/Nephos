#pragma once

#include <imgui/core/imgui.h>
#include <glm/glm.hpp>
#include <memory>

namespace vk{class Structure;}
namespace vk::gui{class Render;}
namespace utl::media{class Image;}
namespace utl::base{class Data;}


namespace vk::interface{

class Render
{
public:
  //Constructor / Destructor
  Render(vk::Structure* vk_struct);
  ~Render();

public:
  //Main function
  void draw_render_texture(glm::vec2 dimension);
  void draw_texture(utl::base::Data& data, std::shared_ptr<utl::media::Image> image);

private:
  vk::Structure* vk_struct;
  vk::gui::Render* vk_render;
};

}
