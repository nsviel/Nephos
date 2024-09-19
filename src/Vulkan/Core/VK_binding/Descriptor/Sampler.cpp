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
void Sampler::create_sampler(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::descriptor::structure::Descriptor& descriptor){
  //---------------------------

  std::shared_ptr<vk::descriptor::structure::Sampler> sampler = std::make_shared<vk::descriptor::structure::Sampler>();
  sampler->name = descriptor.name;
  sampler->binding = descriptor.binding;
  sampler->type = descriptor.type;

  descriptor_set.map_sampler[descriptor.name] = std::move(sampler);

  //---------------------------
}
void Sampler::actualize_sampler(vk::descriptor::structure::Descriptor_set& descriptor_set){
  //---------------------------

  for(auto& [name, sampler] : descriptor_set.map_sampler){
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
    write_sampler.descriptorType = sampler->type;
    write_sampler.descriptorCount = 1;
    write_sampler.pImageInfo = &image_info;

    vkUpdateDescriptorSets(vk_struct->core.device.handle, 1, &write_sampler, 0, nullptr);
  }

  //---------------------------
}
void Sampler::actualize_sampler(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::structure::Image* image){
  //---------------------------

  auto sampler = query_sampler(descriptor_set, image->name);
  if(!sampler) return;

  VkDescriptorImageInfo image_info = {};
  image_info.imageLayout = image->layout;
  image_info.imageView = image->view;
  image_info.sampler = image->sampler;

  VkWriteDescriptorSet write_sampler = {};
  write_sampler.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  write_sampler.dstSet = descriptor_set.handle;
  write_sampler.dstBinding = sampler->binding;
  write_sampler.dstArrayElement = 0;
  write_sampler.descriptorType = sampler->type;
  write_sampler.descriptorCount = 1;
  write_sampler.pImageInfo = &image_info;

  vkUpdateDescriptorSets(vk_struct->core.device.handle, 1, &write_sampler, 0, nullptr);

  //---------------------------
}

//Subfunction
std::shared_ptr<vk::descriptor::structure::Sampler> Sampler::query_sampler(vk::descriptor::structure::Descriptor_set& descriptor_set, std::string& name){
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
