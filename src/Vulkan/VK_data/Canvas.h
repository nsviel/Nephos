#pragma once

#include <Utility/Specific/Common.h>

namespace vk::data{class Buffer;}
namespace vk::data{class Data;}
namespace vk::structure{class Vulkan;}


namespace vk::data{

class Canvas
{
public:
  //Constructor / Destructor
  Canvas(vk::structure::Vulkan* struct_vulkan);
  ~Canvas();

public:
  //Main functions
  void init();
  void clean();

private:
  vk::structure::Vulkan* struct_vulkan;
  Buffer* vk_buffer;
  vk::data::Data* vk_data;
};

}
