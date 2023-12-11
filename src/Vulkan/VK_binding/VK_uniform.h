#pragma once

#include <VK_struct/Namespace.h>
#include <ENG_shader/EDL/EDL_param.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_memory;


class VK_uniform
{
public:
  //Constructor / Destructor
  VK_uniform(Struct_vulkan* struct_vulkan);
  ~VK_uniform();

public:
  //Main functions
  void create_uniform_buffers(vk::structure::Binding* binding);
  vk::structure::Uniform* create_uniform_buffer(string name, size_t size, int binding);
  void clean_uniform(vk::structure::Binding* binding);

  //uniform update
  template <typename T> void update_uniform(string uniform_name, vk::structure::Binding* binding, T value);

private:
  Struct_vulkan* struct_vulkan;
  VK_memory* vk_memory;
};
