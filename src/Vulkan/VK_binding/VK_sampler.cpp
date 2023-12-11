#include "VK_sampler.h"

#include <Vulkan/VK_struct/Namespace.h>


//Constructor / Destructor
VK_sampler::VK_sampler(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_sampler::~VK_sampler(){}

//Main function
void VK_sampler::create_sampler(vk::structure::Binding* binding){
  binding->vec_sampler.clear();
  //---------------------------

  vec_descriptor_required& vec_required = binding->vec_required_binding;
  vector<vk::structure::Sampler*>& vec_sampler = binding->vec_sampler;

  for(int i=0; i<vec_required.size(); i++){
    descriptor_required& descriptor = vec_required[i];
    string name = get<0>(descriptor);
    int binding = get<2>(descriptor);
    VkDescriptorType type = get<3>(descriptor);

    if(type == TYP_IMAGE_SAMPLER || type == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE){
      vk::structure::Sampler* sampler = create_sampler_obj(name, binding, type);
      vec_sampler.push_back(sampler);
    }
  }

  //---------------------------
}
vk::structure::Sampler* VK_sampler::create_sampler_obj(string name, int binding, VkDescriptorType type){
  vk::structure::Sampler* sampler = new vk::structure::Sampler();
  //---------------------------

  sampler->name = name;
  sampler->binding = binding;
  sampler->type = type;

  //---------------------------
  return sampler;
}
