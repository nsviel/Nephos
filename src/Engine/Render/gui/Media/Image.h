#pragma once

#include <Utility/Specific/common.h>

class Engine;
class VK_texture;


namespace eng::render::gui{

class Image
{
public:
  //Constructor / Destructor
  Image(Engine* engine);
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
  VK_texture* vk_texture;
  ImTextureID texture;
};

}
