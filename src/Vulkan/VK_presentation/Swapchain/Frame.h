#pragma once

namespace vk::structure{class Vulkan;}
namespace vk::image{class Image;}
namespace vk::image{class Color;}


namespace vk::presentation{

class Frame
{
public:
  //Constructor / Destructor
  Frame(vk::structure::Vulkan* vk_struct);
  ~Frame();

public:
  //Main function
  void create_frame();
  void clean_frame();

private:
  vk::structure::Vulkan* vk_struct;
  vk::image::Image* vk_image;
  vk::image::Color* vk_color;
};

}