#ifndef ENGINE_H
#define ENGINE_H

class Param;
class ENG_data;
class Window;
class ENG_camera;
class VK_engine;
class ENG_shader;
class ENG_renderpass;


class Engine
{
public:
  //Constructor / Destructor
  Engine(Window* window);
  ~Engine();

public:
  void init();
  void loop();
  void exit();
  void reset();
  void wait_for_gpu_idle();

  inline ENG_camera* get_eng_camera(){return eng_camera;}
  inline Param* get_param(){return param;}
  inline ENG_data* get_eng_data(){return dataManager;}
  inline Window* get_window(){return window;}
  inline VK_engine* get_vk_engine(){return vk_engine;}
  inline ENG_shader* get_eng_shader(){return eng_shader;}

private:
  Param* param;
  ENG_camera* eng_camera;
  ENG_data* dataManager;
  Window* window;
  VK_engine* vk_engine;
  ENG_shader* eng_shader;
  ENG_renderpass* eng_renderpass;
};

#endif
