#include "Storage_image.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::descriptor{

//Constructor / Destructor
Storage_image::Storage_image(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Storage_image::~Storage_image(){}

//Main function
void Storage_image::create_descriptor(vk::structure::Descriptor_set& descriptor_set, vk::structure::Descriptor& descriptor){
  //---------------------------

  std::shared_ptr<vk::structure::Storage_image> storage = std::make_shared<vk::structure::Storage_image>();
  storage->name = descriptor.name;
  storage->binding = descriptor.binding;

  descriptor_set.map_storage_image[descriptor.name] = std::move(storage);

  //---------------------------
}
void Storage_image::actualize_storage(vk::structure::Descriptor_set& descriptor_set){
  //---------------------------

  for(auto& [name, storage] : descriptor_set.map_storage_image){;
    if(!storage->image) continue;

    //Descriptor image info
    VkDescriptorImageInfo image_info = {};
    image_info.imageLayout = storage->image->layout;
    image_info.imageView = storage->image->view;
    image_info.sampler = storage->image->sampler;

    //Write descriptor info
    VkWriteDescriptorSet write_sampler = {};
    write_sampler.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_sampler.dstSet = descriptor_set.handle;
    write_sampler.dstBinding = storage->binding;
    write_sampler.dstArrayElement = 0;
    write_sampler.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    write_sampler.descriptorCount = 1;
    write_sampler.pImageInfo = &image_info;

    vkUpdateDescriptorSets(vk_struct->core.device.handle, 1, &write_sampler, 0, nullptr);
  }

  //---------------------------
}
void Storage_image::actualize_storage(vk::structure::Descriptor_set& descriptor_set, vk::structure::Storage_image& storage, vk::structure::Image& image){
  //---------------------------

  VkDescriptorImageInfo image_info = {};
  image_info.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
  image_info.imageView = image.view;
  image_info.sampler = image.sampler;

  VkWriteDescriptorSet write_sampler = {};
  write_sampler.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  write_sampler.dstSet = descriptor_set.handle;
  write_sampler.dstBinding = storage.binding;
  write_sampler.dstArrayElement = 0;
  write_sampler.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
  write_sampler.descriptorCount = 1;
  write_sampler.pImageInfo = &image_info;

  vkUpdateDescriptorSets(vk_struct->core.device.handle, 1, &write_sampler, 0, nullptr);

  //---------------------------
}

//Subfunction
std::shared_ptr<vk::structure::Storage_image> Storage_image::query_storage(vk::structure::Descriptor_set& descriptor_set, std::string name){
  //---------------------------

  auto it = descriptor_set.map_storage_image.find(name);
  if(it == descriptor_set.map_storage_image.end()){
    std::cout<<"------------------------"<<std::endl;
    std::cout<<"[error] Update storage -> name not recognized \033[1;31m"<<name<<"\033[0m"<<std::endl;
    std::cout<<"Existing storage image names: "<<std::endl;

    for(auto& [name, storage] : descriptor_set.map_storage_image){
      std::cout<<"\033[1;32m"<<name<<"\033[0m"<<std::endl;
    }

    std::cout<<"------------------------"<<std::endl;
    return nullptr;
  }

  //---------------------------
  return it->second;
}

}
