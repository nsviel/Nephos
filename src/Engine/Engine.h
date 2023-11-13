#ifndef ENGINE_H
#define ENGINE_H

#include <ENG_camera/ENG_camera.h>

class Param;
class ENG_data;
class UTL_window;
class ENG_camera;
class Vulkan;
class ENG_shader;
class ENG_renderpass;


class Engine
{
public:
  //Constructor / Destructor
  Engine(UTL_window* utl_window);
  ~Engine();

public:
  void init();
  void loop();
  void exit();
  void reset();
  void wait();

  inline UTL_window* get_ele_window(){return utl_window;}
  inline Vulkan* get_eng_vulkan(){return eng_vulkan;}
  inline Struct_camera* get_camera(){return eng_camera->get_camera();};
  inline ENG_camera* get_eng_camera(){return eng_camera;}
  inline ENG_data* get_eng_data(){return eng_data;}
  inline ENG_shader* get_eng_shader(){return eng_shader;}

private:
  ENG_camera* eng_camera;
  ENG_data* eng_data;
  UTL_window* utl_window;
  Vulkan* eng_vulkan;
  ENG_shader* eng_shader;
  ENG_renderpass* eng_renderpass;
};

#endif
