#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


class VK_info
{
public:
  //Constructor / Destructor
  VK_info(vk::structure::Vulkan* struct_vulkan);
  ~VK_info();

public:
  //Main functions
  inline string get_gpu_name(){return struct_vulkan->device.struct_device.name;}
  inline float get_fps(){return struct_vulkan->profiler.engine_fps;}
  inline int* get_fps_max(){return &struct_vulkan->param.max_fps;}
  inline vec4* get_color_background(){return &struct_vulkan->param.background_color;}
  inline vector<vk::structure::Task>& get_profiler_data(){return struct_vulkan->profiler.vec_task;}

private:
  vk::structure::Vulkan* struct_vulkan;
};
