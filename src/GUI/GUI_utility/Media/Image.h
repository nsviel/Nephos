#pragma once

#include <Utility/UTL_specific/common.h>

class GUI;
class VK_texture;


namespace gui::media{

class Image
{
public:
  //Constructor / Destructor
  Image(GUI* gui);
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
