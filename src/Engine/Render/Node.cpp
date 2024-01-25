#include "Node.h"

#include <Engine/Render/Namespace.h>


namespace eng::shader{

Node::Node(Engine* engine){
  //---------------------------

  this->edl_shader = new eng::shader::EDL(engine);
  this->sce_shader = new eng::shader::SCE(engine);
  this->gui_shader = new eng::render::gui::Shader(engine, &show_panel);
  this->gui_render = new eng::render::gui::Renderer(engine);

  this->show_panel = false;

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete edl_shader;
  delete sce_shader;

  //---------------------------
}

//Main function
void Node::init(){
  //---------------------------

  gui_shader->init_panel();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_shader->run_panel();
  gui_render->run_panel();

  //---------------------------
}


}
