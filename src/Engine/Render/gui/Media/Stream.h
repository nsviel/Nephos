#pragma once

#include <Utility/Specific/common.h>

#include <Vulkan/VK_struct/Namespace.h>

class Engine;
class VK_texture;


namespace eng::render::gui{

class Stream
{
public:
  //Constructor / Destructor
  Stream(Engine* engine);
  ~Stream();

public:
  //Main function
  void draw_stream(utl::media::Image* struct_image, ImVec2 image_size);

  //Subfunction
  void convert_data_into_texture(utl::media::Image* struct_image);
  void render_image(ImVec2& imageSize);

private:
  VK_texture* vk_texture;

  vk::structure::Image* vk_image;
  ImTextureID texture;
};

}
