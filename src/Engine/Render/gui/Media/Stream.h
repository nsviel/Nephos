#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace vk::main{class Texture;}
namespace vk::structure{class Image;}


namespace eng::render::gui{

class Stream
{
public:
  //Constructor / Destructor
  Stream(eng::Node* engine);
  ~Stream();

public:
  //Main function
  void draw_stream(utl::media::Image* utl_image, ImVec2 size);

  //Subfunction
  void convert_data_into_texture(utl::media::Image* utl_image);
  void render_image(ImVec2& size);

private:
  vk::main::Texture* vk_texture;

  vk::structure::Image* vk_image;
  ImTextureID texture;
};

}
