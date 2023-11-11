#ifndef VK_WINDOW_H
#define VK_WINDOW_H

#include <ELE_specific/common.h>

class Struct_vulkan;
class ELE_window;


class VK_surface
{
public:
  //Constructor / Destructor
  VK_surface(Struct_vulkan* struct_vulkan);
  ~VK_surface();

public:
  //Main functions
  void init_window();
  void init_surface();
  void clean_surface();

  //Subfunction
  void check_for_resizing();
  void window_extensions();

private:
  Struct_vulkan* struct_vulkan;
};

#endif
