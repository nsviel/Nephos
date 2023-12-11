#include "VK_descriptor.h"

#include <VK_struct/Namespace.h>
#include <VK_binding/VK_uniform.h>
#include <VK_binding/VK_sampler.h>


//Constructor / Destructor
VK_descriptor::VK_descriptor(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_uniform = new VK_uniform(struct_vulkan);
  this->vk_sampler = new VK_sampler(struct_vulkan);

  //---------------------------
}
VK_descriptor::~VK_descriptor(){}

//Main function
void VK_descriptor::create_binding(vk::structure::Binding* binding){
  //---------------------------

  vk_uniform->create_uniform_buffers(binding);
  vk_sampler->create_sampler(binding);
  this->allocate_descriptor_set(binding);
  this->update_descriptor_uniform(binding);

  //---------------------------
}
void VK_descriptor::clean_binding(vk::structure::Binding* binding){
  //---------------------------

  vkDestroyDescriptorSetLayout(struct_vulkan->device.device, binding->descriptor.layout, nullptr);
  vk_uniform->clean_uniform(binding);

  //---------------------------
}

//Descriptor set update
void VK_descriptor::update_descriptor_uniform(vk::structure::Binding* binding){
  //---------------------------

  //Make list of writeable uniform
  vector<VkWriteDescriptorSet> vec_descriptor_write;
  vector<VkDescriptorBufferInfo> vec_descriptor_buffer_info;
  for(int i=0; i<binding->vec_uniform.size(); i++){
    vk::structure::Uniform* uniform = binding->vec_uniform[i];

    VkDescriptorBufferInfo descriptor_info = {};
    descriptor_info.buffer = uniform->buffer;
    descriptor_info.offset = 0;
    descriptor_info.range = uniform->size;
    vec_descriptor_buffer_info.push_back(descriptor_info);
  }

  for(int i=0; i<binding->vec_uniform.size(); i++){
    vk::structure::Uniform* uniform = binding->vec_uniform[i];
    VkWriteDescriptorSet write_uniform = {};
    write_uniform.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_uniform.dstSet = binding->descriptor.set;
    write_uniform.dstBinding = uniform->binding;
    write_uniform.dstArrayElement = 0;
    write_uniform.descriptorType = TYP_UNIFORM;
    write_uniform.descriptorCount = 1;
    write_uniform.pBufferInfo = &vec_descriptor_buffer_info[i];
    vec_descriptor_write.push_back(write_uniform);
  }

  //Update descriptor
  if(vec_descriptor_write.size() != 0){
    vkUpdateDescriptorSets(struct_vulkan->device.device, static_cast<uint32_t>(vec_descriptor_write.size()), vec_descriptor_write.data(), 0, nullptr);
  }

  //---------------------------
}
void VK_descriptor::update_descriptor_sampler(vk::structure::Binding* binding, vector<vk::structure::Image*> vec_image){
  //---------------------------

  //For each sampler struct in binding struct search for image with same name in vec_image
  //and then update the corresponding shader sampler
  vector<VkWriteDescriptorSet> vec_descriptor_write;
  vector<VkDescriptorImageInfo> vec_descriptor_image_info;
  for(int i=0; i<binding->vec_sampler.size(); i++){
    vk::structure::Sampler* sampler = binding->vec_sampler[i];

    for(int j=0; j<vec_image.size(); j++){
      vk::structure::Image* image = vec_image[j];

      if(sampler->name == image->name){
        VkDescriptorImageInfo image_info = {};
        image_info.imageLayout = image->layout;
        image_info.imageView = image->view;
        image_info.sampler = image->sampler;
        vec_descriptor_image_info.push_back(image_info);

        VkWriteDescriptorSet write_sampler = {};
        write_sampler.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        write_sampler.dstSet = binding->descriptor.set;
        write_sampler.dstBinding = sampler->binding;
        write_sampler.dstArrayElement = 0;
        write_sampler.descriptorType = sampler->type;
        write_sampler.descriptorCount = 1;
        write_sampler.pImageInfo = &vec_descriptor_image_info[vec_descriptor_image_info.size()-1];
        vec_descriptor_write.push_back(write_sampler);
      }
    }
  }

  if(vec_descriptor_write.size() != 0){
    vkUpdateDescriptorSets(struct_vulkan->device.device, static_cast<uint32_t>(vec_descriptor_write.size()), vec_descriptor_write.data(), 0, nullptr);
  }

  //---------------------------
}
void VK_descriptor::update_descriptor_sampler(vk::structure::Binding* binding, vk::structure::Image* image){
  //---------------------------

  vk::structure::Sampler* sampler = nullptr;
  for(int i=0; i<binding->vec_sampler.size(); i++){
    if(image->name == binding->vec_sampler[i]->name){
      sampler = binding->vec_sampler[i];
    }
  }
  if(sampler == nullptr){
    cout<<"------------------------"<<endl;
    cout<<"[error] Update sampler -> name not recognized \033[1;31m"<<image->name<<"\033[0m"<<endl;
    cout<<"Existing uniform names: "<<endl;

    for(int i=0; i<binding->vec_sampler.size(); i++){
      vk::structure::Sampler* sampler = binding->vec_sampler[i];
      cout<<"\033[1;32m"<<sampler->name<<"\033[0m"<<endl;
    }

    cout<<"------------------------"<<endl;
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

  vkUpdateDescriptorSets(struct_vulkan->device.device, 1, &write_sampler, 0, nullptr);

  //---------------------------
}

//Subfunction
void VK_descriptor::cmd_bind_descriptor(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline, VkDescriptorSet set){
  //---------------------------

  vkCmdBindDescriptorSets(command_buffer, TYP_BIND_PIPELINE_GRAPHICS, pipeline->layout, 0, 1, &set, 0, nullptr);

  //---------------------------
}
void VK_descriptor::allocate_descriptor_set(vk::structure::Binding* binding){
  //---------------------------

  VkDescriptorSetAllocateInfo allocation_info{};
  allocation_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocation_info.descriptorPool = struct_vulkan->pool.descriptor;
  allocation_info.descriptorSetCount = 1;
  allocation_info.pSetLayouts = &binding->descriptor.layout;

  VkResult result = vkAllocateDescriptorSets(struct_vulkan->device.device, &allocation_info, &binding->descriptor.set);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }else{
    struct_vulkan->pool.nb_descriptor_allocated++;
  }

  //---------------------------
}
void VK_descriptor::create_layout_from_required(vk::structure::Binding* binding){
  vec_descriptor_required& vec_required_binding = binding->vec_required_binding;
  //---------------------------

  vector<VkDescriptorSetLayoutBinding> vec_binding;
  for(int i=0; i<vec_required_binding.size(); i++){
    descriptor_required& req_binding = vec_required_binding[i];

    //Get descriptor elements
    int binding = get<2>(req_binding);
    VkDescriptorType type = get<3>(req_binding);
    VkShaderStageFlagBits stage = get<4>(req_binding);

    //Convert it into descriptor binding
    VkDescriptorSetLayoutBinding layout_binding{};
    layout_binding.binding = binding;
    layout_binding.descriptorCount = static_cast<uint32_t>(1);
    layout_binding.descriptorType = type;
    layout_binding.stageFlags = stage;
    layout_binding.pImmutableSamplers = nullptr; // Optional
    vec_binding.push_back(layout_binding);
  }

  //Create descriptor layout from requirements
  binding->descriptor.layout = create_layout(vec_binding);

  //---------------------------

}

VkDescriptorSetLayout VK_descriptor::create_layout(vector<VkDescriptorSetLayoutBinding>& vec_binding){
  //---------------------------

  //Combination and info
  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(vec_binding.size());
  layoutInfo.pBindings = vec_binding.data();

  //Descriptor set layout creation
  VkDescriptorSetLayout descriptor_layout;
  VkResult result = vkCreateDescriptorSetLayout(struct_vulkan->device.device, &layoutInfo, nullptr, &descriptor_layout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor set layout!");
  }

  //---------------------------
  return descriptor_layout;
}
