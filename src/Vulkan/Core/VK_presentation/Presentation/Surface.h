#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk{class Structure;}
namespace vk::window{class Window;}


namespace vk::presentation{

class Surface
{
public:
  //Constructor / Destructor
  Surface(vk::Structure* vk_struct);
  ~Surface();

public:
  //Main function
  void init();
  void clean();

  //Subfunction
  VkSurfaceFormatKHR retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& surface_format);

private:
  vk::Structure* vk_struct;
  vk::window::Window* vk_window;
};

}
