#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

#include <Specific/common.h>
#include <GPU/GPU_texture.h>

class Engine;


class GUI_image
{
public:
  //Constructor / Destructor
  GUI_image(Engine* engine);
  ~GUI_image();

public:
  //Main function
  void draw_image(string path);

  //Subfunction
  void load_image(string path);
  void display_image();

  inline voird reload_image(){this->image = nullptr;}

private:
  GPU_texture* gpu_texture;
  VkDescriptorSet descriptor;

  Struct_image* image;
};


#endif
