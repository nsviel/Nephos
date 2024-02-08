#pragma once

#include <Utility/Specific/common.h>

namespace vk{class Node;}
namespace vk::renderpass{class Manager;}
namespace vk::render{class Profiler;}
namespace vk::render{class EDL;}
namespace vk::render{class SCE;}
namespace vk::render::gui{class Shader;}
namespace vk::render::gui{class Renderer;}


namespace vk::render{

class Node : public utl::type::Node
{
public:
  Node(vk::Node* node_vulkan);
  ~Node();

public:
  //Main function
  void init();
  void gui();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline vk::render::EDL* get_shader_edl(){return shader_edl;}
  inline vk::render::SCE* get_shader_scene(){return shader_scene;}

private:
  vk::Node* node_vulkan;
  vk::renderpass::Manager* eng_renderpass;
  vk::render::EDL* shader_edl;
  vk::render::SCE* shader_scene;
  vk::render::gui::Shader* gui_shader;
  vk::render::gui::Renderer* gui_render;
};

}
