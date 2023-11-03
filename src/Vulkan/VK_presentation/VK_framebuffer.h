#ifndef VK_FRAMEBUFFER_H
#define VK_FRAMEBUFFER_H

#include "../VK_struct/struct_frame.h"
#include "../VK_struct/struct_renderpass.h"
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_renderpass;


class VK_framebuffer
{
public:
  //Constructor / Destructor
  VK_framebuffer(VK_engine* vk_engine);
  ~VK_framebuffer();

public:
  //FBO creation
  void create_framebuffer(Struct_renderpass* renderpass, Frame* image);

  //Deletion functions
  void clean_framebuffer(Frame* image);

private:
  Struct_vulkan* vk_struct;
  VK_renderpass* vk_renderpass;
};

#endif
