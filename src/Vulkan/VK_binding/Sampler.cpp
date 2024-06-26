#include "Sampler.h"

#include <Vulkan/Namespace.h>


namespace vk::binding{

//Constructor / Destructor
Sampler::Sampler(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Sampler::~Sampler(){}

//Main function
void Sampler::create_sampler(vk::structure::Binding* binding){
  binding->vec_sampler.clear();
  //---------------------------

  std::vector<vk::structure::Descriptor_required>& vec_required = binding->vec_required_binding;
  vector<vk::structure::Sampler*>& vec_sampler = binding->vec_sampler;

  for(int i=0; i<vec_required.size(); i++){
    vk::structure::Descriptor_required& descriptor = vec_required[i];

    if(descriptor.type == TYP_IMAGE_SAMPLER || descriptor.type == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE){
      vk::structure::Sampler* sampler = create_sampler_obj(descriptor.name, descriptor.binding, descriptor.type);
      vec_sampler.push_back(sampler);
    }
  }

  //---------------------------
}
vk::structure::Sampler* Sampler::create_sampler_obj(std::string name, int binding, VkDescriptorType type){
  vk::structure::Sampler* sampler = new vk::structure::Sampler();
  //---------------------------

  sampler->name = name;
  sampler->binding = binding;
  sampler->type = type;

  //---------------------------
  return sampler;
}

}
