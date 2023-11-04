#ifndef VK_VIEWPORT_H
#define VK_VIEWPORT_H

#include "../VK_struct/struct_viewport.h"
#include "../VK_struct/struct_renderpass.h"
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class Window;


class VK_viewport
{
public:
  VK_viewport(VK_engine* vk_engine);
  ~VK_viewport();

public:
  //Main function
  void init_viewport();
  void cmd_viewport(Struct_renderpass* renderpass);
  void update_viewport();

  //Subfunction
  Struct_viewport* create_viewport();

  inline VkViewport get_viewport(){return viewport;}
  inline VkRect2D get_scissor(){return scissor;}

private:
  Struct_vulkan* struct_vulkan;
  Window* window;

  VkViewport viewport;
  VkRect2D scissor;
};

#endif
