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
void Uniform::create_uniform(vk::binding::structure::Binding& binding, vk::binding::structure::Descriptor& descriptor){
  //---------------------------

  vk::binding::structure::Uniform* uniform = new vk::binding::structure::Uniform();
  uniform->name = descriptor.name;
  uniform->binding = descriptor.binding;
  uniform->size = descriptor.size;

  vk_mem_allocator->create_gpu_buffer(uniform->size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, uniform->buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, uniform->buffer, uniform->mem);
  vkMapMemory(vk_struct->device.handle, uniform->mem, 0, uniform->size, 0, &uniform->mapped);

  binding.map_uniform[descriptor.name] = uniform;

  //---------------------------
}
void Uniform::clean_uniform(vk::binding::structure::Binding& binding){
  //---------------------------

  for(auto& [name, uniform] : binding.map_uniform){
    vkDestroyBuffer(vk_struct->device.handle, uniform->buffer, nullptr);
    vkFreeMemory(vk_struct->device.handle, uniform->mem, nullptr);
  }

  //---------------------------
}

}
