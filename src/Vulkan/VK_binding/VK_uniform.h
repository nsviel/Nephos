#ifndef VK_UNIFORM_H
#define VK_UNIFORM_H

#include <VK_struct/Struct_vk_binding.h>
#include <VK_struct/Struct_pipeline.h>
#include <ENG_shader/EDL/EDL_param.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_buffer;


class VK_uniform
{
public:
  //Constructor / Destructor
  VK_uniform(Struct_vulkan* struct_vulkan);
  ~VK_uniform();

public:
  //Main functions
  void create_uniform_buffers(Struct_vk_binding* binding);
  Struct_vk_uniform* create_uniform_buffer(string name, size_t size, int binding);
  void clean_uniform(Struct_vk_binding* binding);

  //uniform update
  template <typename T> void update_uniform(string uniform_name, Struct_vk_binding* binding, T value);

private:
  Struct_vulkan* struct_vulkan;
  VK_buffer* vk_buffer;
};

#endif
