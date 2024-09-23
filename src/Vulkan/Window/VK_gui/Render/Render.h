#pragma once

#include <imgui/core/imgui.h>
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <memory>

namespace vk{class Structure;}
namespace vk::structure{class Texture;}


namespace vk::gui{

class Render
{
public:
  //Constructor / Destructor
  Render(vk::Structure* vk_struct);
  ~Render();

public:
  //Main function
  void update_render_texture();
  void create_image_descriptor(vk::structure::Texture& texture);
  void display_image(vk::structure::Texture& texture, glm::vec2 dimension);

private:
  vk::Structure* vk_struct;
};

}
