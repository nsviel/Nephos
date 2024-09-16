#include "Profiler.h"

#include <Vulkan/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Profiler::Profiler(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::clear(){
  //---------------------------

  vk_struct->render.profiler.vec_command_buffer.clear();

  //---------------------------
}

}
