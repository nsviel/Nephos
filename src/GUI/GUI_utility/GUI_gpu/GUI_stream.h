#ifndef GUI_STREAM_H
#define GUI_STREAM_H

#include <UTL_specific/common.h>
#include <UTL_struct/Struct_image.h>
#include <VK_struct/Struct_vk_image.h>

class GUI;
class VK_texture;


class GUI_stream
{
public:
  //Constructor / Destructor
  GUI_stream(GUI* gui);
  ~GUI_stream();

public:
  //Main function
  void draw_stream(Struct_image* struct_image, ImVec2 panel_size);

  //Subfunction
  void convert_data_into_texture(Struct_image* struct_image);

private:
  VK_texture* vk_texture;

  Struct_vk_image* image;
  ImTextureID texture;
};


#endif
