#include "Node.h"


namespace eng::shader{

Node::Node(Engine* engine){
  //---------------------------

  this->edl_shader = new eng::shader::EDL(engine);
  this->sce_shader = new eng::shader::SCE(engine);
  //this->gui_shader = new eng::render::gui::Shader(gui, &show_shader, "Shader");
  //this->gui_render = new eng::render::gui::Renderer(gui->get_engine());

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete edl_shader;
  delete sce_shader;

  //---------------------------
}

}
