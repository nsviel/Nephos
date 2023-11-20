#ifndef GUI_VIDEO_H
#define GUI_VIDEO_H

#include <UTL_specific/common.h>



class GUI;
class VK_engine;
class V4L2_video;
class V4L2_camera;


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
  void restart_video();

private:
  VK_engine* vk_engine;
  V4L2_video* utl_video;
  V4L2_camera* utl_stream;

  ImTextureID texture;
};


#endif
