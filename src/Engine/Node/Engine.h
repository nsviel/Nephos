#pragma once

#include <Utility/Node/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Render/Namespace.h>

class Param;
class Vulkan;
class ENG_renderpass;


class Engine
{
public:
  //Constructor / Destructor
  Engine(utility::Node* utility);
  ~Engine();

public:
  void init();
  void loop();
  void exit();
  void reset();
  void wait();

  inline utility::Node* get_utility(){return utility;}
  inline Vulkan* get_eng_vulkan(){return eng_vulkan;}
  inline eng::structure::Camera* get_camera(){return eng_camera->get_camera();};
  inline eng::camera::Node* get_eng_camera(){return eng_camera;}
  inline eng::data::Node* get_eng_data(){return eng_data;}
  inline eng::render::ENG_shader* get_eng_shader(){return eng_shader;}

private:
  utility::Node* utility;
  eng::camera::Node* eng_camera;
  eng::data::Node* eng_data;
  Vulkan* eng_vulkan;
  eng::render::ENG_shader* eng_shader;
  ENG_renderpass* eng_renderpass;
};
