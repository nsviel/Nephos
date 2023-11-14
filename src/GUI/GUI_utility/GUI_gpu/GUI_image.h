#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

#include <UTL_specific/common.h>

class GUI;
class VK_engine;


class GUI_image
{
public:
  //Constructor / Destructor
  GUI_image(GUI* gui);
  ~GUI_image();

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
  VK_engine* vk_engine;
  ImTextureID texture;
};


#endif
