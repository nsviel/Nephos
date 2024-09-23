#pragma once

#include <imgui/core/imgui.h>
#include <vulkan/vulkan.h>
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
  void render_image_in_gui(vk::structure::Texture& texture, glm::vec2 dimension);
  ImTextureID query_render_texture();

private:
  vk::Structure* vk_struct;
};

}
