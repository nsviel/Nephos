#ifndef ENGINE_H
#define ENGINE_H

class Param;
class Data;
class Window;
class Camera;
class VK_engine;
class GPU_data;
class Shader;


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

  inline Camera* get_cameraManager(){return cameraManager;}
  inline Param* get_param(){return param;}
  inline Data* get_dataManager(){return dataManager;}
  inline Window* get_window(){return window;}
  inline VK_engine* get_vk_engine(){return vk_engine;}
  inline GPU_data* get_gpu_data(){return gpu_data;}
  inline Shader* get_shaderManager(){return shaderManager;}

private:
  Param* param;
  Camera* cameraManager;
  Data* dataManager;
  Window* window;
  GPU_data* gpu_data;
  VK_engine* vk_engine;
  Shader* shaderManager;
};

#endif
