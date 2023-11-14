#ifndef GUI_VIDEO_H
#define GUI_VIDEO_H

#include <UTL_specific/common.h>



class GUI;
class VK_engine;
class UTL_video;


class GUI_video
{
public:
  //Constructor / Destructor
  GUI_video(GUI* gui);
  ~GUI_video();

public:
  //Main function
  void draw_video(string path);

  //Subfunction
  void convert_data_into_texture(uint8_t* data);
  void display_frame();

private:
  VK_engine* vk_engine;
  UTL_video* utl_video;

  ImTextureID texture;
};


#endif
