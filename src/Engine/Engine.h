#pragma once

#include <Utility/Node/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Shader/Namespace.h>
#include <Engine/Capture/Node.h>

class Param;
class Vulkan;
class ENG_renderpass;


class Engine
{
public:
  //Constructor / Destructor
  Engine(util::Node* utility);
  ~Engine();

public:
  void init();
  void loop();
  void exit();
  void reset();
  void wait();

  inline util::Node* get_utility(){return utility;}
  inline Vulkan* get_eng_vulkan(){return eng_vulkan;}
  inline eng::data::Camera* get_camera(){return eng_camera->get_camera();};
  inline eng::camera::Node* get_eng_camera(){return eng_camera;}
  inline eng::scene::Node* get_eng_data(){return eng_data;}
  inline eng::shader::Shader* get_eng_shader(){return eng_shader;}
  inline eng::capture::Node* get_eng_capture(){return eng_capture;}

private:
  util::Node* utility;
  eng::camera::Node* eng_camera;
  eng::scene::Node* eng_data;
  eng::capture::Node* eng_capture;
  Vulkan* eng_vulkan;
  eng::shader::Shader* eng_shader;
  ENG_renderpass* eng_renderpass;
};
