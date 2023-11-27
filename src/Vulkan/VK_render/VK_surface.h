#ifndef VK_WINDOW_H
#define VK_WINDOW_H

#include <UTL_specific/common.h>

class Struct_vulkan;
class UTL_window;


class VK_surface
{
public:
  //Constructor / Destructor
  VK_surface(Struct_vulkan* struct_vulkan);
  ~VK_surface();

public:
  //Main functions
  void init();
  void clean();

  //Subfunction
  void check_for_resizing();

private:
  Struct_vulkan* struct_vulkan;
};

#endif
