#include "Sampler.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::descriptor{

//Constructor / Destructor
Sampler::Sampler(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Sampler::~Sampler(){}

//Main function
void Sampler::create_sampler(vk::structure::Descriptor_set& descriptor_set, vk::structure::Descriptor& descriptor){
  //---------------------------

  std::shared_ptr<vk::structure::Sampler> sampler = std::make_shared<vk::structure::Sampler>();
  sampler->name = descriptor.name;
  sampler->binding = descriptor.binding;

  descriptor_set.map_sampler[descriptor.name] = std::move(sampler);

  //---------------------------
}
void Sampler::actualize_sampler(vk::structure::Descriptor_set& descriptor_set){
  //---------------------------

  for(auto& [name, sampler] : descriptor_set.map_sampler){;
    if(!sampler->image) continue;

    //Descriptor image info
    VkDescriptorImageInfo image_info = {};
    image_info.imageLayout = sampler->image->layout;
    image_info.imageView = sampler->image->view;
    image_info.sampler = sampler->image->sampler;

    //Write descriptor info
    VkWriteDescriptorSet write_sampler = {};
    write_sampler.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_sampler.dstSet = descriptor_set.handle;
    write_sampler.dstBinding = sampler->binding;
    write_sampler.dstArrayElement = 0;
    write_sampler.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    write_sampler.descriptorCount = 1;
    write_sampler.pImageInfo = &image_info;

    vkUpdateDescriptorSets(vk_struct->core.device.handle, 1, &write_sampler, 0, nullptr);
  }

  //---------------------------
}
void Sampler::actualize_sampler(vk::structure::Descriptor_set& descriptor_set, vk::structure::Sampler& sampler, vk::structure::Image& image){
  //---------------------------

  VkDescriptorImageInfo image_info = {};
  image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  image_info.imageView = image.view;
  image_info.sampler = image.sampler;

  VkWriteDescriptorSet write_sampler = {};
  write_sampler.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  write_sampler.dstSet = descriptor_set.handle;
  write_sampler.dstBinding = sampler.binding;
  write_sampler.dstArrayElement = 0;
  write_sampler.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  write_sampler.descriptorCount = 1;
  write_sampler.pImageInfo = &image_info;

  vkUpdateDescriptorSets(vk_struct->core.device.handle, 1, &write_sampler, 0, nullptr);

  //---------------------------
}

//Subfunction
std::shared_ptr<vk::structure::Sampler> Sampler::query_sampler(vk::structure::Descriptor_set& descriptor_set, std::string name){
  //---------------------------

  auto it = descriptor_set.map_sampler.find(name);
  if (it == descriptor_set.map_sampler.end()) {
    std::cout<<"------------------------"<<std::endl;
    std::cout<<"[error] Update sampler -> name not recognized \033[1;31m"<<name<<"\033[0m"<<std::endl;
    std::cout<<"Existing uniform names: "<<std::endl;

    for(auto& [name, sampler] : descriptor_set.map_sampler){
      std::cout<<"\033[1;32m"<<name<<"\033[0m"<<std::endl;
    }

    std::cout<<"------------------------"<<std::endl;
    return nullptr;
  }

  //---------------------------
  return it->second;
}

}
