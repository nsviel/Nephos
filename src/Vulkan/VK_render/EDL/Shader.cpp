#include "Shader.h"

#include <Vulkan/Namespace.h>


namespace vk::render::edl{

Shader::Shader(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  //this->edl_struct = new vk::render::structure::EDL();

  //---------------------------
}
Shader::~Shader(){}

//Main function
void Shader::update_shader(){
  //---------------------------



  //---------------------------
}

}
