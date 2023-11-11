#include "VK_uniform.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_data/VK_buffer.h>


//Constructor / Destructor
VK_uniform::VK_uniform(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_buffer = new VK_buffer(struct_vulkan);

  //---------------------------
}
VK_uniform::~VK_uniform(){}

//Uniform creation
void VK_uniform::create_uniform_buffers(Struct_binding* binding){
  binding->vec_uniform.clear();
  //---------------------------

  vec_descriptor_required& vec_required = binding->vec_required_binding;
  vector<Struct_uniform*>& vec_uniform = binding->vec_uniform;

  for(int i=0; i<vec_required.size(); i++){
    descriptor_required& descriptor = vec_required[i];
    string name = get<0>(descriptor);
    size_t size = get<1>(descriptor);
    int binding = get<2>(descriptor);
    VkDescriptorType type = get<3>(descriptor);

    if(type == TYP_UNIFORM){
      Struct_uniform* uniform = create_uniform_buffer(name, size, binding);
      vec_uniform.push_back(uniform);
    }
  }

  //---------------------------
}
Struct_uniform* VK_uniform::create_uniform_buffer(string name, size_t size, int binding){
  Struct_uniform* uniform = new Struct_uniform();
  //---------------------------

    uniform->name = name;
    uniform->binding = binding;
    uniform->size = size;

    vk_buffer->create_gpu_buffer(size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, uniform->buffer);
    vk_buffer->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, uniform->buffer, uniform->mem);
    vkMapMemory(struct_vulkan->device.device, uniform->mem, 0, size, 0, &uniform->mapped);

  //---------------------------
  return uniform;
}
void VK_uniform::clean_uniform(Struct_binding* binding){
  //---------------------------

  for(int i=0; i<binding->vec_uniform.size(); i++){
    Struct_uniform* uniform = binding->vec_uniform[i];
    vkDestroyBuffer(struct_vulkan->device.device, uniform->buffer, nullptr);
    vkFreeMemory(struct_vulkan->device.device, uniform->mem, nullptr);
  }

  //---------------------------
}

//Uniform update
template <typename T> void VK_uniform::update_uniform(string uniform_name, Struct_binding* binding, T value){
  bool has_been_found = false;
  //---------------------------

  for(int i = 0; i < binding->vec_uniform.size(); i++){
    Struct_uniform* uniform = binding->vec_uniform[i];
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
      Struct_uniform* uniform = binding->vec_uniform[i];
      cout << "\033[1;32m" << uniform->name << "\033[0m" << endl;
    }

    cout << "------------------------" << endl;
    exit(0);
  }

  //---------------------------
}
template void VK_uniform::update_uniform(string uniform_name, Struct_binding* binding, glm::mat4 value);
template void VK_uniform::update_uniform(string uniform_name, Struct_binding* binding, int value);
template void VK_uniform::update_uniform(string uniform_name, Struct_binding* binding, EDL_param value);
