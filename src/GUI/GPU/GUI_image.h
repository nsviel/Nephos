#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

#include <Specific/common.h>

class Engine;
class GPU_texture;


class GUI_image
{
public:
  //Constructor / Destructor
  GUI_image(Engine* engine);
  ~GUI_image();

public:
  //Main function
  void display_image(string path);

private:
  GPU_texture* gpu_texture;
};


#endif
