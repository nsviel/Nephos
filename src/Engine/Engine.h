#ifndef ENGINE_H
#define ENGINE_H

#include <ENG_camera/ENG_camera.h>

class Param;
class ENG_data;
class ELE_window;
class ENG_camera;
class Vulkan;
class VK_engine;
class ENG_shader;
class ENG_renderpass;


class Engine
{
public:
  //Constructor / Destructor
  Engine(ELE_window* ele_window);
  ~Engine();

public:
  void init();
  void loop();
  void exit();
  void reset();
  void wait_for_gpu_idle();

  inline ELE_window* get_ele_window(){return ele_window;}
  inline Vulkan* get_eng_vulkan(){return vk_engine;}
  inline VK_engine* get_vk_engine(){return eng_vulkan;}
  inline Struct_camera* get_camera(){return eng_camera->get_camera();};
  inline ENG_camera* get_eng_camera(){return eng_camera;}
  inline ENG_data* get_eng_data(){return dataManager;}
  inline ENG_shader* get_eng_shader(){return eng_shader;}

private:
  ENG_camera* eng_camera;
  ENG_data* dataManager;
  ELE_window* ele_window;
  Vulkan* eng_vulkan;
  VK_engine* vk_engine;
  ENG_shader* eng_shader;
  ENG_renderpass* eng_renderpass;
};

#endif
