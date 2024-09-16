#include "Binding.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::binding{

//Constructor / Destructor
Binding::Binding(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::binding::Uniform(vk_struct);
  this->vk_sampler = new vk::binding::Sampler(vk_struct);
  this->vk_layout = new vk::binding::Layout(vk_struct);
  this->vk_descriptor_set = new vk::binding::Descriptor_set(vk_struct);

  //---------------------------
}
Binding::~Binding(){}

//Main function
void Binding::create_binding(vk::binding::structure::Binding& binding){
  //---------------------------

  vk_layout->create_layout(binding.layout);
  vk_descriptor_set->allocate(binding);

  //---------------------------
}
void Binding::clean_binding(vk::binding::structure::Binding& binding){
  //---------------------------

  vk_descriptor_set->clean(binding);
  vk_uniform->clean_uniform(binding.layout);

  //---------------------------
}



}
