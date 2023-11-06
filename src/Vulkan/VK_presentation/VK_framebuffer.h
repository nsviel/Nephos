#ifndef VK_FRAMEBUFFER_H
#define VK_FRAMEBUFFER_H

#include "../VK_struct/Struct_frame.h"
#include "../VK_struct/Struct_renderpass.h"
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;


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
  Struct_vulkan* struct_vulkan;
};

#endif
