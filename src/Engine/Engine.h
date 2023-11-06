#ifndef ENGINE_H
#define ENGINE_H

class Param;
class ENG_data;
class Window;
class ENG_camera;
class VK_engine;
class Shader;
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
  inline ENG_data* get_dataManager(){return dataManager;}
  inline Window* get_window(){return window;}
  inline VK_engine* get_vk_engine(){return vk_engine;}
  inline Shader* get_shaderManager(){return shaderManager;}

private:
  Param* param;
  ENG_camera* eng_camera;
  ENG_data* dataManager;
  Window* window;
  VK_engine* vk_engine;
  Shader* shaderManager;
  ENG_renderpass* eng_renderpass;
};

#endif
