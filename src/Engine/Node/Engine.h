#pragma once

#include <Engine/ENG_camera/ENG_camera.h>

class Param;
class Utility;
class ENG_data;
class ENG_camera;
class Vulkan;
class ENG_shader;
class ENG_renderpass;


class Engine
{
public:
  //Constructor / Destructor
  Engine(Utility* utility);
  ~Engine();

public:
  void init();
  void loop();
  void exit();
  void reset();
  void wait();

  inline Utility* get_utility(){return utility;}
  inline Vulkan* get_eng_vulkan(){return eng_vulkan;}
  inline eng::structure::Camera* get_camera(){return eng_camera->get_camera();};
  inline ENG_camera* get_eng_camera(){return eng_camera;}
  inline ENG_data* get_eng_data(){return eng_data;}
  inline ENG_shader* get_eng_shader(){return eng_shader;}

private:
  Utility* utility;
  ENG_camera* eng_camera;
  ENG_data* eng_data;
  Vulkan* eng_vulkan;
  ENG_shader* eng_shader;
  ENG_renderpass* eng_renderpass;
};
