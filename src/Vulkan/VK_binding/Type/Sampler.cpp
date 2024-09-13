#include "Sampler.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::binding{

//Constructor / Destructor
Sampler::Sampler(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Sampler::~Sampler(){}

//Main function
void Sampler::create_sampler(vk::binding::structure::Binding* binding){
  //---------------------------

  std::vector<vk::binding::structure::Required>& vec_required = binding->vec_required_binding;

  for(int i=0; i<vec_required.size(); i++){
    vk::binding::structure::Required& descriptor = vec_required[i];

    if(descriptor.type == TYP_IMAGE_SAMPLER || descriptor.type == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE){
      vk::binding::structure::Sampler* sampler = new vk::binding::structure::Sampler();
      sampler->name = descriptor.name;
      sampler->binding = descriptor.binding;
      sampler->type = descriptor.type;

      binding->map_sampler[descriptor.name] = sampler;
    }
  }

  //---------------------------
}
void Sampler::update_sampler(vk::binding::structure::Binding* binding, vk::structure::Image* image){
  //---------------------------

  vk::binding::structure::Sampler* sampler = binding->map_sampler[image->name];
  if(sampler == nullptr){
    std::cout<<"------------------------"<<std::endl;
    std::cout<<"[error] Update sampler -> name not recognized \033[1;31m"<<image->name<<"\033[0m"<<std::endl;
    std::cout<<"Existing uniform names: "<<std::endl;

    for(auto& [name, sampler] : binding->map_sampler){
      std::cout<<"\033[1;32m"<<name<<"\033[0m"<<std::endl;
    }

    std::cout<<"------------------------"<<std::endl;
    exit(0);
  }

  VkDescriptorImageInfo image_info = {};
  image_info.imageLayout = image->layout;
  image_info.imageView = image->view;
  image_info.sampler = image->sampler;

  VkWriteDescriptorSet write_sampler = {};
  write_sampler.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  write_sampler.dstSet = binding->descriptor.set;
  write_sampler.dstBinding = sampler->binding;
  write_sampler.dstArrayElement = 0;
  write_sampler.descriptorType = sampler->type;
  write_sampler.descriptorCount = 1;
  write_sampler.pImageInfo = &image_info;

  vkUpdateDescriptorSets(vk_struct->device.handle, 1, &write_sampler, 0, nullptr);

  //---------------------------
}

//Subfunction
vk::binding::structure::Required Sampler::sampler_color(){
  //---------------------------

  vk::binding::structure::Required descriptor;
  descriptor.name = "tex_color";
  descriptor.size = 0;
  descriptor.binding = 1;
  descriptor.type = TYP_IMAGE_SAMPLER;
  descriptor.stage = TYP_SHADER_FS;

  //---------------------------
  return descriptor;
}
vk::binding::structure::Required Sampler::sampler_depth(){
  //---------------------------

  vk::binding::structure::Required descriptor;
  descriptor.name = "tex_depth";
  descriptor.size = 0;
  descriptor.binding = 4;
  descriptor.type = TYP_IMAGE_SAMPLER;
  descriptor.stage = TYP_SHADER_FS;

  //---------------------------
  return descriptor;
}

}
