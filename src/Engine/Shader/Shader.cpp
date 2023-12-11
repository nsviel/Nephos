#include "Shader.h"


namespace eng::shader{

Shader::Shader(Engine* engine){
  //---------------------------

  this->edl_shader = new eng::shader::EDL(engine);
  this->psr_shader = new eng::shader::PSR(engine);
  this->sce_shader = new eng::shader::SCE(engine);

  //---------------------------
}
Shader::~Shader(){
  //---------------------------

  delete edl_shader;
  delete psr_shader;
  delete sce_shader;

  //---------------------------
}

}
