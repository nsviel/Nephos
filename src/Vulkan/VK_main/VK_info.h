#ifndef VK_INFO_H
#define VK_INFO_H

#include <VK_struct/Struct_vulkan.h>
#include <VK_struct/Struct_param.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class Struct_param;


class VK_info
{
public:
  //Constructor / Destructor
  VK_info(VK_engine* vk_engine);
  ~VK_info();

public:
  //Main functions
  inline string get_gpu_name(){return struct_vulkan->info.gpu_name;}
  inline float get_fps(){return struct_vulkan->info.engine_fps;}
  inline int* get_fps_max(){return &struct_param->max_fps;}
  inline vec4* get_color_background(){return &struct_param->background_color;}

private:
  Struct_vulkan* struct_vulkan;
  Struct_param* struct_param;

};

#endif
