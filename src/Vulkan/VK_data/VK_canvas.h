#pragma once

#include <Utility/Specific/common.h>

namespace vk::data{class Buffer;}
namespace vk::data{class VK_data;}
namespace vk::structure{class Vulkan;}


namespace vk::data{

class VK_canvas
{
public:
  //Constructor / Destructor
  VK_canvas(vk::structure::Vulkan* struct_vulkan);
  ~VK_canvas();

public:
  //Main functions
  void init();
  void clean();

private:
  vk::structure::Vulkan* struct_vulkan;
  Buffer* vk_buffer;
  vk::data::VK_data* vk_data;
};

}
