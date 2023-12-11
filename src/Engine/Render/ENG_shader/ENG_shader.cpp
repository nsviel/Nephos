#include "ENG_shader.h"
#include "EDL/EDL_shader.h"
#include "PSR/PSR_shader.h"
#include "Scene/SCE_shader.h"


namespace eng::shader{

ENG_shader::ENG_shader(Engine* engine){
  //---------------------------

  this->edl_shader = new EDL_shader(engine);
  this->psr_shader = new PSR_shader(engine);
  this->sce_shader = new SCE_shader(engine);

  //---------------------------
}
ENG_shader::~ENG_shader(){
  //---------------------------

  delete edl_shader;
  delete psr_shader;
  delete sce_shader;

  //---------------------------
}

}
