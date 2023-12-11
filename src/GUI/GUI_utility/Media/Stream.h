#pragma once

#include <UTL_specific/common.h>
#include <UTL_base/Struct_image.h>
#include <VK_struct/Namespace.h>

class GUI;
class VK_texture;


namespace gui::media{

class Stream
{
public:
  //Constructor / Destructor
  Stream(GUI* gui);
  ~Stream();

public:
  //Main function
  void draw_stream(data::Image* struct_image, ImVec2 panel_size);

  //Subfunction
  void convert_data_into_texture(data::Image* struct_image);

private:
  VK_texture* vk_texture;

  vk::structure::Image* vk_image;
  ImTextureID texture;
};

}
