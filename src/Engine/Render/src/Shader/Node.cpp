#include "Node.h"


namespace eng::shader{

Node::Node(Engine* engine){
  //---------------------------

  this->edl_shader = new eng::shader::EDL(engine);
  this->sce_shader = new eng::shader::SCE(engine);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete edl_shader;
  delete sce_shader;

  //---------------------------
}

}
