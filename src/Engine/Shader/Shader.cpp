#include "Shader.h"


namespace eng::shader{

Shader::Shader(Engine* engine){
  //---------------------------

  this->edl_shader = new eng::shader::EDL_shader(engine);
  this->psr_shader = new eng::shader::PSR_shader(engine);
  this->sce_shader = new eng::shader::SCE_shader(engine);

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
