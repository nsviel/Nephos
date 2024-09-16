#include "Binding.h"

#include <Vulkan/Namespace.h>


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

  vk_layout->create_layout(binding);
  this->create_descriptor(binding);
  vk_descriptor_set->allocate(binding);
  vk_descriptor_set->update(binding);

  //---------------------------
}
void Binding::clean_binding(vk::binding::structure::Binding& binding){
  //---------------------------

  vk_descriptor_set->clean(binding);
  vk_uniform->clean_uniform(binding);

  //---------------------------
}

//Subfunction
void Binding::create_descriptor(vk::binding::structure::Binding& binding){
  //---------------------------

  for(auto& descriptor : binding.vec_descriptor){

    switch(descriptor.type){
      case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:{
        vk_sampler->create_sampler(binding, descriptor);
        break;
      }
      case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:{
        vk_uniform->create_uniform(binding, descriptor);
        break;
      }
    }

  }

  //---------------------------
}

}
