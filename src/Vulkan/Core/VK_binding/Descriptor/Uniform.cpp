#include "Uniform.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::descriptor{

//Constructor / Destructor
Uniform::Uniform(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);

  //---------------------------
}
Uniform::~Uniform(){}

//Uniform creation
void Uniform::create_uniform(vk::descriptor::structure::Layout& layout, vk::descriptor::structure::Descriptor& descriptor){
  //---------------------------

  vk::descriptor::structure::Uniform* uniform = new vk::descriptor::structure::Uniform();
  uniform->name = descriptor.name;
  uniform->binding = descriptor.binding;
  uniform->size = descriptor.size;

  vk_mem_allocator->create_gpu_buffer(uniform->size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, uniform->buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, uniform->buffer, uniform->mem);
  vkMapMemory(vk_struct->core.device.handle, uniform->mem, 0, uniform->size, 0, &uniform->mapped);

  layout.map_uniform[descriptor.name] = uniform;

  //---------------------------
}
void Uniform::clean_uniform(vk::descriptor::structure::Layout& layout){
  //---------------------------

  for(auto& [name, uniform] : layout.map_uniform){
    vkDestroyBuffer(vk_struct->core.device.handle, uniform->buffer, nullptr);
    vkFreeMemory(vk_struct->core.device.handle, uniform->mem, nullptr);
  }

  //---------------------------
}

}
