#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk{class Structure;}
namespace vk::image{class Ressource;}
namespace vk::presentation{class Surface;}
namespace vk::structure{class Image;}


namespace vk::image{

class Color
{
public:
  //Constructor / Destructor
  Color(vk::Structure* vk_struct);
  ~Color();

public:
  //Main function
  void create_window_image(vk::structure::Image* color);
  void create_screenshot_image(vk::structure::Image* color);
  
  //Subfunction
  VkFormat find_color_format();

private:
  vk::Structure* vk_struct;
  vk::image::Ressource* vk_image;
  vk::presentation::Surface* vk_surface;
};

}
