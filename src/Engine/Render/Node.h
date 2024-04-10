#pragma once

#include <Utility/Specific/Common.h>

namespace vk{class Node;}
namespace utl{class Node;}
namespace eng::cam{class Node;}
namespace eng::scene{class Node;}
namespace ope{class Node;}

namespace eng::renderpass{class Manager;}
namespace eng::render{class Profiler;}
namespace rnd::edl{class Shader;}
namespace rnd::scene{class Shader;}


namespace eng::render{

class Node : public utl::type::Node
{
public:
  Node(eng::Node* engine);
  ~Node();

public:
  //Main function
  void init();
  void gui();

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
  eng::renderpass::Manager* eng_renderpass;
  rnd::edl::Shader* shader_edl;
  rnd::scene::Shader* shader_scene;

};

}
