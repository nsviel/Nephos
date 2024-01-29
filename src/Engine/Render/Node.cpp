#include "Node.h"

#include <Engine/Render/Namespace.h>


namespace eng::render{

Node::Node(eng::Node* engine){
  //---------------------------

  this->engine = engine;
  this->shader_edl = new eng::shader::EDL(this);
  this->shader_scene = new eng::shader::SCE(this);
  this->eng_renderpass = new eng::renderpass::Manager(this);
  this->gui_shader = new eng::render::gui::Shader(this, &show_shader);
  this->gui_render = new eng::render::gui::Renderer(this);
  this->gui_profiler = new eng::render::gui::Profiler(this, &show_profiler);

  this->show_shader = false;
  this->show_profiler = true;

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
  gui_profiler->run_panel();

  //---------------------------
}


}
