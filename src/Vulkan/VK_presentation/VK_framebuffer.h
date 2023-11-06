#ifndef VK_FRAMEBUFFER_H
#define VK_FRAMEBUFFER_H

#include "../VK_struct/Struct_framebuffer.h"
#include "../VK_struct/Struct_renderpass.h"
#include <ELE_specific/common.h>

class VK_engine;
class VK_color;
class VK_depth;
class VK_image;
class Struct_vulkan;


class VK_framebuffer
{
public:
  //Constructor / Destructor
  VK_framebuffer(VK_engine* vk_engine);
  ~VK_framebuffer();

public:
  void create_framebuffer(Struct_renderpass* renderpass);
  //FBO creation
  void clean_frame_renderpass(Struct_renderpass* renderpass);

  //Subfunction
  void create_framebuffer_obj(Struct_renderpass* renderpass, Struct_framebuffer* image);
  void clean_framebuffer_obj(Struct_framebuffer* image);

private:
  Struct_vulkan* struct_vulkan;
  VK_color* vk_color;
  VK_depth* vk_depth;
  VK_image* vk_image;
};

#endif
