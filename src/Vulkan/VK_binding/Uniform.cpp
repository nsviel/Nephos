#include "Uniform.h"

#include <Vulkan/Namespace.h>
#include <Engine/Render/Namespace.h>


namespace vk::binding{

//Constructor / Destructor
Uniform::Uniform(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_memory = new vk::command::Memory(struct_vulkan);

  //---------------------------
}
Uniform::~Uniform(){}

//Uniform creation
void Uniform::create_uniform_buffers(vk::structure::Binding* binding){
  binding->vec_uniform.clear();
  //---------------------------

  vec_descriptor_required& vec_required = binding->vec_required_binding;
  vector<vk::structure::Uniform*>& vec_uniform = binding->vec_uniform;

  for(int i=0; i<vec_required.size(); i++){
    descriptor_required& descriptor = vec_required[i];
    string name = get<0>(descriptor);
    size_t size = get<1>(descriptor);
    int binding = get<2>(descriptor);
    VkDescriptorType type = get<3>(descriptor);

    if(type == TYP_UNIFORM){
      vk::structure::Uniform* uniform = create_uniform_buffer(name, size, binding);
      vec_uniform.push_back(uniform);
    }
  }

  //---------------------------
}
vk::structure::Uniform* Uniform::create_uniform_buffer(string name, size_t size, int binding){
  vk::structure::Uniform* uniform = new vk::structure::Uniform();
  //---------------------------

    uniform->name = name;
    uniform->binding = binding;
    uniform->size = size;

    vk_memory->create_gpu_buffer(size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, uniform->buffer);
    vk_memory->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, uniform->buffer, uniform->mem);
    vkMapMemory(struct_vulkan->device.device, uniform->mem, 0, size, 0, &uniform->mapped);

  //---------------------------
  return uniform;
}
void Uniform::clean_uniform(vk::structure::Binding* binding){
  //---------------------------

  for(int i=0; i<binding->vec_uniform.size(); i++){
    vk::structure::Uniform* uniform = binding->vec_uniform[i];
    vkDestroyBuffer(struct_vulkan->device.device, uniform->buffer, nullptr);
    vkFreeMemory(struct_vulkan->device.device, uniform->mem, nullptr);
  }

  //---------------------------
}

//Uniform update
template <typename T> void Uniform::update_uniform(string uniform_name, vk::structure::Binding* binding, T value){
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
  if (!has_been_found) {
    cout << "------------------------" << endl;
    cout << "[error] Update uniform -> name not recognized \033[1;31m" << uniform_name << "\033[0m" << endl;
    cout << "Existing uniform names: " << endl;

    for (int i = 0; i < binding->vec_uniform.size(); i++) {
      vk::structure::Uniform* uniform = binding->vec_uniform[i];
      cout << "\033[1;32m" << uniform->name << "\033[0m" << endl;
    }

    cout << "------------------------" << endl;
    exit(0);
  }

  //---------------------------
}
template void Uniform::update_uniform(string uniform_name, vk::structure::Binding* binding, glm::mat4 value);
template void Uniform::update_uniform(string uniform_name, vk::structure::Binding* binding, int value);
template void Uniform::update_uniform(string uniform_name, vk::structure::Binding* binding, eng::shader::EDL_param value);

}
