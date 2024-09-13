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
  vk_uniform->create_uniform_buffers(binding);
  vk_sampler->create_sampler(binding);
  vk_descriptor_set->allocate(binding);
  vk_uniform->update_uniform(binding);

  //---------------------------
}
void Binding::clean_binding(vk::binding::structure::Binding& binding){
  //---------------------------

  vk_descriptor_set->clean(binding);
  vk_uniform->clean_uniform(binding);

  //---------------------------
}

//Subfunction
void Binding::make_object_descriptor(utl::base::Data& data, vk::binding::structure::Binding& binding){
  //---------------------------

  vk::binding::structure::Descriptor descriptor = vk_uniform->uniform_mvp();
  binding.vec_required_binding.push_back(vk_uniform->uniform_mvp());

  if(data.topology.type == utl::topology::POINT){
    vk::binding::structure::Descriptor descriptor = vk_uniform->uniform_point_size();
    binding.vec_required_binding.push_back(vk_uniform->uniform_point_size());
  }

  //---------------------------

}

}