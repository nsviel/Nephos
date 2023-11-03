#ifndef VK_WINDOW_H
#define VK_WINDOW_H

#include <ELE_specific/common.h>

class VK_engine;
class VK_struct;
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
  void clean_surface();

  //Subfunction
  void create_window_surface();
  void check_for_resizing();
  void get_required_extensions();

  inline Window* get_window(){return window;}
  inline vec2 get_window_dim(){return window_dim;}

private:
  Window* window;
  VK_struct* vk_struct;

  vec2 window_dim;
};

#endif
