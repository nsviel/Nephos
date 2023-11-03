#ifndef VK_BINDING_H
#define VK_BINDING_H

#include "../VK_struct/struct_binding.h"
#include "../VK_struct/struct_pipeline.h"
#include "../VK_struct/struct_data.h"
#include <ELE_specific/common.h>

class VK_engine;
class VK_struct;
class VK_descriptor;
class VK_uniform;
class VK_sampler;


class VK_binding
{
public:
  //Constructor / Destructor
  VK_binding(VK_engine* vk_engine);
  ~VK_binding();

public:
  //Main functions
  void create_binding(Struct_binding* binding);
  void clean_binding(Struct_binding* binding);

  void update_uniform(Struct_binding* binding, mat4 mvp);

  inline VK_uniform* get_vk_uniform(){return vk_uniform;}

private:
  VK_struct* vk_struct;
  VK_uniform* vk_uniform;
  VK_descriptor* vk_descriptor;
  VK_sampler* vk_sampler;
};

#endif
