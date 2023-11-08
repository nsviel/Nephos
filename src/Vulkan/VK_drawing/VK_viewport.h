#ifndef VK_VIEWPORT_H
#define VK_VIEWPORT_H

#include <VK_struct/Struct_viewport.h>
#include <VK_struct/Struct_renderpass.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class ELE_window;


class VK_viewport
{
public:
  VK_viewport(VK_engine* vk_engine);
  ~VK_viewport();

public:
  //Main function
  void init_viewport();
  void cmd_viewport(Struct_subpass* subpass);
  void update_viewport();

  //Subfunction
  Struct_viewport* create_viewport();

private:
  Struct_vulkan* struct_vulkan;
  ELE_window* ele_window;
};

#endif
