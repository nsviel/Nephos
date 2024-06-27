#include "Interface.h"

#include <Vulkan/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Interface::Interface(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Interface::~Interface(){}

//Main function
void Interface::fill_profiler_info(){
  //---------------------------


  //---------------------------
}
std::string Interface::get_gpu_name(){
  return vk_struct->device.physical_device.name;
}
glm::vec4* Interface::get_color_background(){
  return &vk_struct->param.background_color;
}
bool Interface::is_gpu_discrete(){
  return vk_struct->device.physical_device.discrete_gpu;
}

}
