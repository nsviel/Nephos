#include "Shader.h"
#include "EDL/EDL_shader.h"
#include "PSR/PSR_shader.h"
#include "Canvas/CAN_shader.h"
#include "Scene/SCE_shader.h"


Shader::Shader(Engine* engine){
  //---------------------------

  this->edl_shader = new EDL_shader(engine);
  this->psr_shader = new PSR_shader(engine);
  this->can_shader = new CAN_shader(engine);
  this->sce_shader = new SCE_shader(engine);

  //---------------------------
}
Shader::~Shader(){
  //---------------------------

  delete edl_shader;
  delete psr_shader;
  delete can_shader;
  delete sce_shader;

  //---------------------------
}
