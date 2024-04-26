#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace vk::image{class Texture;}


namespace gui::element{

class Image
{
public:
  //Constructor / Destructor
  Image(eng::Node* engine);
  ~Image();

public:
  //Main function
  void draw_image_static(string path);
  void draw_image_dynamic(string path);
  void draw_image_bin(string path);

  //Subfunction
  void load_image_static(string path);
  void load_image_dynamic(string path);
  void load_image_bin(string path);
  void display_image();

private:
  vk::image::Texture* vk_texture;
  utl::media::Image* utl_image;
};

}
