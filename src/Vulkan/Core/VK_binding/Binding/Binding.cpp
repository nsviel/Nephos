#include "Binding.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::descriptor{

//Constructor / Destructor
Binding::Binding(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_sampler = new vk::descriptor::Sampler(vk_struct);
  this->vk_layout = new vk::descriptor::Layout(vk_struct);
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);

  //---------------------------
}
Binding::~Binding(){}

//Main function
void Binding::create_binding(vk::descriptor::structure::Binding& binding){
  //---------------------------

  vk_layout->create_layout(binding.layout);
  vk_descriptor_set->allocate(binding);

  //---------------------------
}
void Binding::clean_binding(vk::descriptor::structure::Binding& binding){
  //---------------------------

  vk_descriptor_set->clean(binding);
  vk_uniform->clean_uniform(binding.layout);

  //---------------------------
}



}
