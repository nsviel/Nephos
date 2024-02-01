#include "Node.h"

#include <Engine/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::render{

Node::Node(eng::Node* engine){
  utl::gui::Panel* sha_panel = new_panel("Shader", ICON_FA_ROAD, false);
  //---------------------------

  this->engine = engine;
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
