#pragma once

#include <Utility/Specific/common.h>

namespace vk{class Node;}
namespace vk::main{class Texture;}


namespace vk::render::gui{

class Image
{
public:
  //Constructor / Destructor
  Image(vk::Node* engine);
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
  vk::main::Texture* vk_texture;
  ImTextureID imgui_texture;
};

}
