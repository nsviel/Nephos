#include "Dimension.h"

#include <Vulkan/Namespace.h>


namespace vk::window{

//Constructor / Destructor
Dimension::Dimension(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Dimension::~Dimension(){}

//Main function
glm::vec2 Dimension::get_dimension(){
  return vk_struct->window.dimension;
}
glm::vec2 Dimension::get_center(){
  return vk_struct->window.center;
}
void Dimension::set_center(glm::vec2 value){
  vk_struct->window.center = value;
}

}
