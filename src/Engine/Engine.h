#ifndef ENGINE_H
#define ENGINE_H

class Param;
class Data;
class Window;
class Camera;
class VK_engine;
class GPU_data;
class GPU_texture;
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
  inline Data* get_data(){return data;}
  inline Window* get_window(){return window;}
  inline VK_engine* get_vk_engine(){return vk_engine;}
  inline GPU_data* get_gpu_data(){return gpu_data;}
  inline GPU_texture* get_gpu_texture(){return gpu_texture;}
  inline Shader* get_shaderManager(){return shaderManager;}

private:
  Param* param;
  Camera* cameraManager;
  Data* data;
  Window* window;
  GPU_data* gpu_data;
  GPU_texture* gpu_texture;
  VK_engine* vk_engine;
  Shader* shaderManager;
};

#endif
