#ifndef VK_WINDOW_H
#define VK_WINDOW_H

#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class ELE_window;


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

  inline ELE_window* get_ele_window(){return ele_window;}

private:
  ELE_window* ele_window;
  Struct_vulkan* struct_vulkan;
};

#endif
