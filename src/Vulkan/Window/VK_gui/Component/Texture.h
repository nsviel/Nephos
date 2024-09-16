#pragma once

#include <imgui/implot/implot.h>
#include <memory>

namespace vk{class Structure;}
namespace vk::image{class Texture;}
namespace utl::media{class Image;}


namespace vk::gui{

class Texture
{
public:
  //Constructor / Destructor
  Texture(vk::Structure* vk_struct);
  ~Texture();

public:
  //Main function
  void insert_texture(std::shared_ptr<utl::media::Image> utl_image);
  void update_render_texture();
  ImTextureID create_imgui_texture(int UID);
  ImTextureID query_render_texture();

private:
  vk::Structure* vk_struct;
  vk::image::Texture* vk_texture;
};

}
