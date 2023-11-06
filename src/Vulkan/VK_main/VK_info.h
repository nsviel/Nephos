#ifndef VK_INFO_H
#define VK_INFO_H

#include <VK_struct/Struct_vulkan.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;


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

private:
  Struct_vulkan* struct_vulkan;

};

#endif
