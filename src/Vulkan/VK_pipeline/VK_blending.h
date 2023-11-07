#ifndef VK_BLENDING_H
#define VK_BLENDING_H

#include <VK_struct/Struct_pipeline.h>
#include <VK_struct/Struct_renderpass.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;


class VK_blending
{
public:
  //Constructor / Destructor
  VK_blending(VK_engine* vk_engine);
  ~VK_blending();

public:
  //Main functions
  void create_color_blending_state(Struct_pipeline* pipeline);
  void create_color_blending(Struct_pipeline* pipeline);

private:
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
};

#endif
