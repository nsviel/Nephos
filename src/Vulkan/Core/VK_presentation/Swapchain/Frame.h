#pragma once

namespace vk{class Structure;}
namespace vk::image{class Image;}
namespace vk::image{class Color;}


namespace vk::presentation{

class Frame
{
public:
  //Constructor / Destructor
  Frame(vk::Structure* vk_struct);
  ~Frame();

public:
  //Main function
  void create_frame();
  void clean_frame();

private:
  vk::Structure* vk_struct;
  vk::image::Image* vk_image;
  vk::image::Color* vk_color;
};

}
