#include "Uniform.h"

#include <Vulkan/Namespace.h>


namespace vk::binding{

//Constructor / Destructor
Uniform::Uniform(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);

  //---------------------------
}
Uniform::~Uniform(){}

//Uniform creation
void Uniform::create_uniform_buffers(vk::structure::Binding* binding){
  binding->vec_uniform.clear();
  //---------------------------

  std::vector<vk::structure::Descriptor_required>& vec_required = binding->vec_required_binding;
  vector<vk::structure::Uniform*>& vec_uniform = binding->vec_uniform;

  for(int i=0; i<vec_required.size(); i++){
    vk::structure::Descriptor_required& descriptor = vec_required[i];

    if(descriptor.type == TYP_UNIFORM){
      vk::structure::Uniform* uniform = create_uniform_buffer(descriptor.name, descriptor.size, descriptor.binding);
      vec_uniform.push_back(uniform);
    }
  }

  //---------------------------
}
vk::structure::Uniform* Uniform::create_uniform_buffer(std::string name, size_t size, int binding){
  vk::structure::Uniform* uniform = new vk::structure::Uniform();
  //---------------------------

    uniform->name = name;
    uniform->binding = binding;
    uniform->size = size;

    vk_mem_allocator->create_gpu_buffer(size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, uniform->buffer);
    vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, uniform->buffer, uniform->mem);
    vkMapMemory(vk_struct->device.handle, uniform->mem, 0, size, 0, &uniform->mapped);

  //---------------------------
  return uniform;
}
void Uniform::clean_uniform(vk::structure::Binding* binding){
  //---------------------------

  for(int i=0; i<binding->vec_uniform.size(); i++){
    vk::structure::Uniform* uniform = binding->vec_uniform[i];
    vkDestroyBuffer(vk_struct->device.handle, uniform->buffer, nullptr);
    vkFreeMemory(vk_struct->device.handle, uniform->mem, nullptr);
  }

  //---------------------------
}

//Uniform update
template <typename T> void Uniform::update_uniform(std::string uniform_name, vk::structure::Binding* binding, T value){
  bool has_been_found = false;
  //---------------------------

  for(int i = 0; i < binding->vec_uniform.size(); i++){
    vk::structure::Uniform* uniform = binding->vec_uniform[i];
    if(uniform->name == uniform_name){
      memcpy(uniform->mapped, &value, sizeof(value));
      has_been_found = true;
      break;
    }
  }

  //Error reporte
  if(!has_been_found){
    cout << "------------------------" << endl;
    cout << "[error] Update uniform -> name not recognized \033[1;31m" << uniform_name << "\033[0m" << endl;
    cout << "Existing uniform names: " << endl;

    for(int i = 0; i < binding->vec_uniform.size(); i++){
      vk::structure::Uniform* uniform = binding->vec_uniform[i];
      cout << "\033[1;32m" << uniform->name << "\033[0m" << endl;
    }

    cout << "------------------------" << endl;
    exit(0);
  }

  //---------------------------
}
template void Uniform::update_uniform(std::string uniform_name, vk::structure::Binding* binding, glm::mat4 value);
template void Uniform::update_uniform(std::string uniform_name, vk::structure::Binding* binding, int value);
template void Uniform::update_uniform(std::string uniform_name, vk::structure::Binding* binding, vk::render::edl::Structure value);

}
