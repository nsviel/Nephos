#pragma once

#include <Utility/Specific/common.h>

class Param;
class Vulkan;
namespace eng::renderpass{class ENG_renderpass;}
namespace utl{class Node;}
namespace eng::cam{class Node;}
namespace eng::scene{class Node;}
namespace eng::shader{class Node;}
namespace eng::capture{class Node;}
namespace eng::ope{class Node;}


class Engine
{
public:
  //Constructor / Destructor
  Engine(utl::Node* utility);
  ~Engine();

public:
  void init();
  void loop();
  void gui();
  void exit();
  void reset();
  void wait();

  inline utl::Node* get_node_utility(){return utility;}
  inline Vulkan* get_eng_vulkan(){return eng_vulkan;}
  inline eng::cam::Node* get_node_camera(){return node_camera;}
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline eng::shader::Node* get_node_shader(){return node_shader;}
  inline eng::capture::Node* get_node_capture(){return node_capture;}

private:
  Vulkan* eng_vulkan;
  eng::renderpass::ENG_renderpass* eng_renderpass;
  utl::Node* utility;
  eng::cam::Node* node_camera;
  eng::scene::Node* node_scene;
  eng::capture::Node* node_capture;
  eng::shader::Node* node_shader;
  eng::ope::Node* node_operation;
};
