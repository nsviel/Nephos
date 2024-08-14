#pragma once

#include <imgui/core/imgui.h>

namespace eng{class Node;}
namespace vk::image{class Texture;}
namespace vk::gui{class Imgui;}
namespace vk::structure{class Texture;}
namespace utl::media{class Image;}


namespace rnd::gui{

class Stream
{
public:
  //Constructor / Destructor
  Stream(eng::Node* node_engine);
  ~Stream();

public:
  //Main function
  void draw_stream(utl::media::Image* utl_image, ImVec2 dimension);

  //Subfunction
  bool check_image(utl::media::Image* utl_image);
  void convert_data_into_texture(utl::media::Image* utl_image);
  void render_image(utl::media::Image* utl_image, ImVec2& dimension);

private:
  vk::image::Texture* vk_texture;
  vk::gui::Imgui* vk_imgui;

  float current_timestamp = -1;
  int current_UID = -1;
};

}
