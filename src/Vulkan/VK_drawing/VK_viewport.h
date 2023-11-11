#ifndef VK_VIEWPORT_H
#define VK_VIEWPORT_H

#include <VK_struct/Struct_viewport.h>
#include <VK_struct/Struct_renderpass.h>
#include <ELE_specific/common.h>

class Struct_vulkan;


class VK_viewport
{
public:
  VK_viewport(Struct_vulkan* struct_vulkan);
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
};

#endif
