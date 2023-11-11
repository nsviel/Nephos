#ifndef VK_POOL_H
#define VK_POOL_H

#include <ELE_specific/common.h>

class Struct_vulkan;


class VK_pool
{
public:
  //Constructor / Destructor
  VK_pool(Struct_vulkan* struct_vulkan);
  ~VK_pool();

public:
  //Main functions
  void init();
  void clean();

  //Descriptor pool
  void create_descriptor_pool();
  void clean_descriptor_pool();

  //Command pool
  void create_command_pool();
  void reset_command_pool();
  void clean_command_pool();

private:
  Struct_vulkan* struct_vulkan;
};

#endif
