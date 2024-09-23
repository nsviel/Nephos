#pragma once

#include <imgui/core/imgui.h>
#include <glm/glm.hpp>
#include <memory>

namespace vk{class Structure;}
namespace vk::gui{class Render;}
namespace vk::data{class Function;}
namespace vk::gui{class Imgui;}
namespace vk::shader{class Reloader;}
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
  void draw_image(std::shared_ptr<utl::media::Image> image, glm::vec2 dimension);
  void reload_shader();
  void new_frame();

private:
  vk::Structure* vk_struct;
  vk::gui::Render* vk_render;
  vk::data::Function* vk_data;
  vk::gui::Imgui* vk_imgui;
  vk::shader::Reloader* vk_shader;
};

}
