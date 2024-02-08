#include "Node.h"

#include <Vulkan/Render/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace vk::render{

Node::Node(vk::Node* node_vulkan){
  utl::gui::Panel* sha_panel = new_panel("Shader", ICON_FA_ROAD, false);
  //---------------------------

  this->node_vulkan = node_vulkan;
  this->shader_edl = new vk::render::EDL(node_vulkan);
  this->shader_scene = new vk::render::SCE(node_vulkan);
  this->eng_renderpass = new vk::renderpass::Manager(node_vulkan);
  this->gui_shader = new vk::render::gui::Shader(node_vulkan, &sha_panel->is_open);
  this->gui_render = new vk::render::gui::Renderer(node_vulkan);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete shader_edl;
  delete shader_scene;

  //---------------------------
}

//Main function
void Node::init(){
  //---------------------------

  //gui_shader->init_panel();
  eng_renderpass->init();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_shader->run_panel();
  gui_render->run_panel();

  //---------------------------
}


}
