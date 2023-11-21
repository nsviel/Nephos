#ifndef GUI_STREAM_H
#define GUI_STREAM_H

#include <UTL_specific/common.h>
#include <UTL_struct/Struct_image.h>

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
  void draw_video(Struct_image* struct_image);

  //Subfunction
  void convert_data_into_texture(Struct_image* struct_image);
  void display_frame();
  void restart_video();

private:
  VK_engine* vk_engine;

  ImTextureID texture;
};


#endif
