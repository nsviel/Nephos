#pragma once

#include <Utility/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Render/src/Shader/Namespace.h>
#include <Engine/Capture/Node.h>

class Param;
class Vulkan;
class ENG_renderpass;


class Engine
{
public:
  //Constructor / Destructor
  Engine(utl::Node* utility);
  ~Engine();

public:
  void init();
  void loop();
  void exit();
  void reset();
  void wait();

  inline utl::Node* get_utility(){return utility;}
  inline Vulkan* get_eng_vulkan(){return eng_vulkan;}
  inline eng::cam::Node* get_node_camera(){return node_camera;}
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline eng::shader::Node* get_node_shader(){return node_shader;}
  inline eng::capture::Node* get_node_capture(){return node_capture;}

private:
  Vulkan* eng_vulkan;
  ENG_renderpass* eng_renderpass;
  utl::Node* utility;
  eng::cam::Node* node_camera;
  eng::scene::Node* node_scene;
  eng::capture::Node* node_capture;
  eng::shader::Node* node_shader;
};
