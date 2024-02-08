#pragma once

#include <Utility/Specific/common.h>

namespace vk{class Node;}
namespace vk::main{class Texture;}
namespace vk::structure{class Texture;}


namespace vk::render::gui{

class Stream
{
public:
  //Constructor / Destructor
  Stream(vk::Node* node_vulkan);
  ~Stream();

public:
  //Main function
  void draw_stream(utl::media::Image* utl_image, ImVec2 size);

  //Subfunction
  void convert_data_into_texture(utl::media::Image* utl_image, ImVec2& size);
  void render_image(ImVec2& size);

private:
  vk::main::Texture* vk_texture;

  vk::structure::Texture* texture;
  ImTextureID imgui_texture;
};

}
