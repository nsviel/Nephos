#ifndef GUI_CAMERA_H
#define GUI_CAMERA_H

#include <UTL_specific/common.h>

class GUI;
class VK_engine;


class GUI_stream
{
public:
  //Constructor / Destructor
  GUI_stream(GUI* gui);
  ~GUI_stream();

public:
  //Main function
  void draw_video(uint8_t* data, int width, int height);

  //Subfunction
  void convert_data_into_texture(uint8_t* data, int width, int height);
  void display_frame();
  void restart_video();

private:
  VK_engine* vk_engine;

  ImTextureID texture;
};


#endif
