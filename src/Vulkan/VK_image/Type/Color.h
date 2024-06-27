#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk::image{class Image;}
namespace vk{class Structure;}
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
  void create_color_image(vk::structure::Image* color);

  //Subfunction
  VkSurfaceFormatKHR retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format);
  VkFormat find_color_format();

private:
  vk::Structure* vk_struct;
  vk::image::Image* vk_image;
};

}
