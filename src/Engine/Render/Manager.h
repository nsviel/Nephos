#pragma once

#include <Utility/Specific/Common.h>

namespace vk{class Node;}
namespace utl{class Node;}
namespace eng{class Node;}
namespace eng::cam{class Node;}
namespace eng::scene{class Node;}
namespace ope{class Node;}

namespace eng::render{class Profiler;}
namespace rnd::edl{class Shader;}
namespace rnd::scene{class Shader;}

namespace eng::render{class Manager;}
namespace rnd::edl{class Renderpass;}
namespace rnd::scene{class Renderpass;}
namespace rnd::gui{class Renderpass;}


namespace eng::render{

class Manager
{
public:
  //Constructor / Destructor
  Manager(eng::Node* node_engine);
  ~Manager();

public:
  //Main functions
  void init();

  inline utl::Node* get_node_utility(){return node_utility;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline eng::cam::Node* get_node_camera(){return node_camera;}
  inline ope::Node* get_node_operation(){return node_operation;}

  inline rnd::edl::Shader* get_shader_edl(){return shader_edl;}
  inline rnd::scene::Shader* get_shader_scene(){return shader_scene;}

private:
  //Dependancy
  vk::Node* node_vulkan;
  ope::Node* node_operation;
  eng::cam::Node* node_camera;
  utl::Node* node_utility;

  //Child
  rnd::edl::Shader* shader_edl;
  rnd::scene::Shader* shader_scene;

  rnd::scene::Renderpass* rp_scene;
  rnd::edl::Renderpass* rp_edl;
  rnd::gui::Renderpass* rp_gui;
};

}
