#ifndef VK_WINDOW_H
#define VK_WINDOW_H

#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class Window;


class VK_surface
{
public:
  //Constructor / Destructor
  VK_surface(VK_engine* vk_engine);
  ~VK_surface();

public:
  //Main functions
  void init_window();
  void init_surface();
  void clean_surface();

  //Subfunction
  void check_for_resizing();
  void window_extensions();

  inline Window* get_window(){return window;}

private:
  Window* window;
  Struct_vulkan* struct_vulkan;
};

#endif
