#pragma once

#include <imgui/implot/implot.h>
#include <memory>

namespace vk{class Structure;}
namespace vk::texture{class Ressource;}
namespace utl::media{class Image;}


namespace vk::gui{

class Render
{
public:
  //Constructor / Destructor
  Render(vk::Structure* vk_struct);
  ~Render();

public:
  //Main function
  void insert_texture(std::shared_ptr<utl::media::Image> utl_image);
  void update_render_texture();
  ImTextureID query_render_texture();

private:
  vk::Structure* vk_struct;
  vk::texture::Ressource* vk_texture;
};

}
