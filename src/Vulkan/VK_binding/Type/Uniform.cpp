#include "Uniform.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::binding{

//Constructor / Destructor
Uniform::Uniform(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);

  //---------------------------
}
Uniform::~Uniform(){}

//Uniform creation
void Uniform::add_uniform(){
  //---------------------------





  //---------------------------
}


void Uniform::create_uniform_buffers(vk::binding::structure::Binding* binding){
  //---------------------------

  std::vector<vk::binding::structure::Required>& vec_required = binding->vec_required_binding;

  for(int i=0; i<vec_required.size(); i++){
    vk::binding::structure::Required& descriptor = vec_required[i];

    if(descriptor.type == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER){
      vk::binding::structure::Uniform* uniform = new vk::binding::structure::Uniform();
      uniform->name = descriptor.name;
      uniform->binding = descriptor.binding;
      uniform->size = descriptor.size;

      vk_mem_allocator->create_gpu_buffer(uniform->size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, uniform->buffer);
      vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, uniform->buffer, uniform->mem);
      vkMapMemory(vk_struct->device.handle, uniform->mem, 0, uniform->size, 0, &uniform->mapped);

      binding->map_uniform[descriptor.name] = uniform;
    }
  }

  //---------------------------
}
void Uniform::clean_uniform(vk::binding::structure::Binding* binding){
  //---------------------------

  for(auto& [name, uniform] : binding->map_uniform){
    vkDestroyBuffer(vk_struct->device.handle, uniform->buffer, nullptr);
    vkFreeMemory(vk_struct->device.handle, uniform->mem, nullptr);
  }

  //---------------------------
}
void Uniform::update_uniform(vk::binding::structure::Binding* binding){
  //---------------------------

  //Make list of writeable uniform
  std::vector<VkWriteDescriptorSet> vec_descriptor_write;
  std::vector<VkDescriptorBufferInfo> vec_descriptor_buffer_info;
  for(auto& [name, uniform] : binding->map_uniform){
    //Blabla
    VkDescriptorBufferInfo descriptor_info = {};
    descriptor_info.buffer = uniform->buffer;
    descriptor_info.offset = 0;
    descriptor_info.range = uniform->size;
    vec_descriptor_buffer_info.push_back(descriptor_info);

    //Blabla
    VkWriteDescriptorSet write_uniform = {};
    write_uniform.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_uniform.dstSet = binding->descriptor_set.set;
    write_uniform.dstBinding = uniform->binding;
    write_uniform.dstArrayElement = 0;
    write_uniform.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    write_uniform.descriptorCount = 1;
    write_uniform.pBufferInfo = &descriptor_info;
    vec_descriptor_write.push_back(write_uniform);
  }

  //Update descriptor
  if(vec_descriptor_write.size() != 0){
    vkUpdateDescriptorSets(vk_struct->device.handle, static_cast<uint32_t>(vec_descriptor_write.size()), vec_descriptor_write.data(), 0, nullptr);
  }

  //---------------------------
}

//Uniform update
template <typename T> void Uniform::update_uniform(std::string uniform_name, vk::binding::structure::Binding* binding, T value){
  bool has_been_found = false;
  //---------------------------

  for(auto& [name, uniform] : binding->map_uniform){
    if(name == uniform_name){
      memcpy(uniform->mapped, &value, sizeof(value));
      has_been_found = true;
      break;
    }
  }

  //Error reporte
  if(!has_been_found){
    std::cout << "------------------------" << std::endl;
    std::cout << "[error] Update uniform -> name not recognized \033[1;31m" << uniform_name << "\033[0m" << std::endl;
    std::cout << "Existing uniform names: " << std::endl;

    for(auto& [name, uniform] : binding->map_uniform){
      std::cout << "\033[1;32m" << name << "\033[0m" << std::endl;
    }

    std::cout << "------------------------" << std::endl;
    exit(0);
  }

  //---------------------------
}
template void Uniform::update_uniform(std::string uniform_name, vk::binding::structure::Binding* binding, glm::mat4 value);
template void Uniform::update_uniform(std::string uniform_name, vk::binding::structure::Binding* binding, int value);
template void Uniform::update_uniform(std::string uniform_name, vk::binding::structure::Binding* binding, vk::render::structure::EDL value);

//Subfunction
vk::binding::structure::Required Uniform::uniform_point_size(){
  //---------------------------

  vk::binding::structure::Required descriptor;
  descriptor.name = "point_size";
  descriptor.size = sizeof(int);
  descriptor.binding = 1;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}
vk::binding::structure::Required Uniform::uniform_mvp(){
  //---------------------------

  vk::binding::structure::Required descriptor;
  descriptor.name = "mvp";
  descriptor.size = sizeof(glm::mat4);
  descriptor.binding = 0;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}
vk::binding::structure::Required Uniform::uniform_edl(){
  //---------------------------

  vk::binding::structure::Required descriptor;
  descriptor.name = "EDL_param";
  descriptor.size = sizeof(vk::render::structure::EDL);
  descriptor.binding = 5;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

  //---------------------------
  return descriptor;
}

}
