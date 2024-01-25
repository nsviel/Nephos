#pragma once

#include <Utility/Specific/common.h>

class VK_memory;
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Binding;}
namespace vk::structure{class Uniform;}


class VK_uniform
{
public:
  //Constructor / Destructor
  VK_uniform(vk::structure::Vulkan* struct_vulkan);
  ~VK_uniform();

public:
  //Main functions
  void create_uniform_buffers(vk::structure::Binding* binding);
  vk::structure::Uniform* create_uniform_buffer(string name, size_t size, int binding);
  void clean_uniform(vk::structure::Binding* binding);

  //uniform update
  template <typename T> void update_uniform(string uniform_name, vk::structure::Binding* binding, T value);

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_memory* vk_memory;
};
