#include "Descriptor.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::pipeline{

//Constructor / Destructor
Descriptor::Descriptor(vk::Structure* vk_struct){
  //---------------------------

  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_sampler = new vk::descriptor::Sampler(vk_struct);
  this->vk_layout = new vk::descriptor::Layout(vk_struct);
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);

  //---------------------------
}
Descriptor::~Descriptor(){}

//Main function
void Descriptor::create_pipeline_descriptor(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_layout->create_layout(pipeline.descriptor.layout);
  vk_descriptor_set->allocate_descriptor_set(pipeline.descriptor.descriptor_set, pipeline.descriptor.layout);

  //---------------------------
}
void Descriptor::clean_pipeline_descriptor(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_uniform->clean_uniform(pipeline.descriptor.descriptor_set);
  vk_layout->clean_layout(pipeline.descriptor.layout);

  //---------------------------
}

//Subfunction
std::shared_ptr<vk::structure::Descriptor_set> Descriptor::query_descriptor_set(vk::structure::Pipeline& pipeline){
  //---------------------------



  //---------------------------
  return nullptr;
}


}
