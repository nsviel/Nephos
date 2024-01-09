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
  inline eng::data::Camera* get_camera(){return node_camera->get_camera();};
  inline eng::camera::Node* get_node_camera(){return node_camera;}
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline eng::shader::Node* get_node_shader(){return node_shader;}
  inline eng::capture::Node* get_node_capture(){return node_capture;}

private:
  util::Node* utility;
  eng::camera::Node* node_camera;
  eng::scene::Node* node_scene;
  eng::capture::Node* node_capture;
  Vulkan* eng_vulkan;
  eng::shader::Node* node_shader;
  ENG_renderpass* eng_renderpass;
};
