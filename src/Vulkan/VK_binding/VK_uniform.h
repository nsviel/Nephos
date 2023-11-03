#ifndef VK_UNIFORM_H
#define VK_UNIFORM_H

#include "../VK_struct/struct_binding.h"
#include "../VK_struct/struct_pipeline.h"
#include <ENG_shader/EDL/EDL_param.h>
#include <ELE_specific/common.h>

class VK_engine;
class VK_struct;
class VK_buffer;
class VK_error;


class VK_uniform
{
public:
  //Constructor / Destructor
  VK_uniform(VK_engine* vk_engine);
  ~VK_uniform();

public:
  //Main functions
  void create_uniform_buffers(Struct_binding* binding);
  Struct_uniform* create_uniform_buffer(string name, size_t size, int binding);
  void clean_uniform(Struct_binding* binding);

  //uniform update
  void update_uniform_mat4(string uniform_name, Struct_binding* binding, glm::mat4& value);
  void update_uniform_int(string uniform_name, Struct_binding* binding, int value);
  void update_uniform_edl(string uniform_name, Struct_binding* binding, EDL_param value);

private:
  VK_struct* vk_struct;
  VK_buffer* vk_buffer;
  VK_error* vk_error;
};

#endif
