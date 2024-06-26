#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace vk::image{class Texture;}
namespace vk::gui{class Imgui;}
namespace vk::structure{class Texture;}


namespace rnd{

class Stream
{
public:
  //Constructor / Destructor
  Stream(eng::Node* node_engine);
  ~Stream();

public:
  //Main function
  void draw_stream(utl::media::Image* utl_image, ImVec2 size);

  //Subfunction
  bool check_image(utl::media::Image* utl_image);
  void convert_data_into_texture(utl::media::Image* utl_image);
  void render_image(utl::media::Image* utl_image, ImVec2& size);

private:
  vk::image::Texture* vk_texture;
  vk::gui::Imgui* vk_imgui;

  int current_UID = -1;
  float current_timestamp = -1;
};

}