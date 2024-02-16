#include "Node.h"

#include <Engine/Namespace.h>
#include <Render/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::render{

Node::Node(eng::Node* node_engine){
  utl::gui::Panel* sha_panel = add_panel("Shader", ICON_FA_ROAD, false);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_utility = node_engine->get_node_utility();
  this->node_vulkan = node_engine->get_node_vulkan();

  //Child
  this->shader_edl = new eng::shader::EDL(this);
  this->shader_scene = new eng::shader::SCE(this);
  this->eng_renderpass = new eng::renderpass::Manager(this);
  this->gui_shader = new eng::render::gui::Shader(this, &sha_panel->is_open);
  this->gui_render = new eng::render::gui::Renderer(this);

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
