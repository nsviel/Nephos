#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

#include <ELE_specific/common.h>

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
  void draw_image(string path);

  //Subfunction
  void load_image(string path);
  void display_image();

private:
  VK_engine* vk_engine;
  VkDescriptorSet descriptor;
};


#endif
