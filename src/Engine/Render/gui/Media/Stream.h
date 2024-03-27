#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace vk::main{class Texture;}
namespace vk::main{class Imgui;}
namespace vk::structure{class Texture;}


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
  bool check_image(utl::media::Image* utl_image);
  void convert_data_into_texture(utl::media::Image* utl_image);
  void render_image(utl::media::Image* utl_image, ImVec2& size);

private:
  vk::main::Texture* vk_texture;
  vk::main::Imgui* vk_imgui;
};

}
