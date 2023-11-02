#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

#include <Specific/common.h>
#include <GPU/GPU_texture.h>

class GUI;


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

  inline void reload_image(){this->image = nullptr;}

private:
  GPU_texture* gpu_texture;
  VkDescriptorSet descriptor;

  Struct_image* image;
};


#endif
