#include "VK_data.h"

#include <VK_data/VK_buffer.h>
#include <VK_main/VK_engine.h>
#include <VK_main/Struct_vulkan.h>
#include <VK_image/VK_texture.h>
#include <VK_command/VK_command_buffer.h>
#include <VK_binding/VK_binding.h>
#include <VK_binding/VK_descriptor.h>


//Constructor / Destructor
VK_data::VK_data(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_buffer = new VK_buffer(vk_engine);
  this->vk_texture = new VK_texture(vk_engine);
  this->vk_binding = new VK_binding(vk_engine);
  this->vk_command_buffer = new VK_command_buffer(vk_engine);
  this->vk_descriptor = new VK_descriptor(vk_engine);

  //---------------------------
}
VK_data::~VK_data(){}

//Insertion function
void VK_data::insert_object(Object* object){
  //---------------------------

  //Creat new data struct
  Struct_data* data = new Struct_data();
  data->object = object;

  //Descriptor
  descriptor_required mvp = std::make_tuple("mvp", sizeof(mat4), 0, TYPE_UNIFORM, STAGE_VS);
  data->binding.vec_required_binding.push_back(mvp);

  if(object->draw_type_name == "point"){
    descriptor_required size = std::make_tuple("point_size", sizeof(int), 1, TYPE_UNIFORM, STAGE_VS);
    data->binding.vec_required_binding.push_back(size);
  }

  //Apply adequat init functions
  this->check_for_attribut(data);
  vk_buffer->create_buffer(data);
  vk_command_buffer->allocate_command_buffer_secondary(data);
  vk_descriptor->create_layout_from_required(&data->binding);
  vk_binding->create_binding(&data->binding);

  //Insert data struct into set
  struct_vulkan->list_object.push_back(data);

  //---------------------------
}

//Clean function
void VK_data::clean_data(Struct_data* data){
  //---------------------------

  vkDeviceWaitIdle(struct_vulkan->device.device);

  vk_buffer->clean_buffer(data);
  vk_texture->clean_texture(data);
  vk_binding->clean_binding(&data->binding);

  //---------------------------
}
void VK_data::clean_data_all(){
  //---------------------------

  for(int i=0; i<struct_vulkan->list_object.size(); i++){
    Struct_data* data = *next(struct_vulkan->list_object.begin(),i);
    this->clean_data(data);
  }

  //---------------------------
}
void VK_data::clean_data_scene(int ID){
  //---------------------------

  for(int i=0; i<struct_vulkan->list_object.size(); i++){
    Struct_data* data = *next(struct_vulkan->list_object.begin(),i);
    if(data->object->ID == ID){
      this->clean_data(data);
      struct_vulkan->list_object.remove(data);
    }
  }

  //---------------------------
}

//Data description
void VK_data::create_data_description(Struct_pipeline* pipeline){
  //---------------------------

  this->create_vertex_description(pipeline);
  this->create_attribut_description(pipeline);
  this->combine_description(pipeline);

  //---------------------------
}
void VK_data::create_attribut_description(Struct_pipeline* pipeline){
  vector<VkVertexInputAttributeDescription> attribut_description;
  //---------------------------

  vector<string>& vec_data_name = pipeline->definition.vec_data_name;
  for(int i=0; i<vec_data_name.size(); i++){
    VkVertexInputAttributeDescription attribut{};

    if(vec_data_name[i] == "location"){
      attribut.binding = 0;
      attribut.location = 0;
      attribut.format = VK_FORMAT_R32G32B32_SFLOAT;
      attribut.offset = 0;
    }
    else if(vec_data_name[i] == "color"){
      attribut.binding = 1;
      attribut.location = 1;
      attribut.format = VK_FORMAT_R32G32B32A32_SFLOAT;
      attribut.offset = 0;
    }
    else if(vec_data_name[i] == "tex_coord"){
      attribut.binding = 2;
      attribut.location = 2;
      attribut.format = VK_FORMAT_R32G32_SFLOAT;
      attribut.offset = 0;
    }
    else{
      cout<<"[error] data description"<<endl;
      break;
    }

    attribut_description.push_back(attribut);
  }

  //---------------------------
  pipeline->info.attribut_description = attribut_description;
}
void VK_data::create_vertex_description(Struct_pipeline* pipeline){
  vector<VkVertexInputBindingDescription> data_description;
  //---------------------------

  vector<string>& vec_data_name = pipeline->definition.vec_data_name;
  for(int i=0; i<vec_data_name.size(); i++){
    VkVertexInputBindingDescription description{};

    if(vec_data_name[i] == "location"){
      description.binding = 0;
      description.stride = sizeof(glm::vec3);
      description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }
    else if(vec_data_name[i] == "color"){
      description.binding = 1;
      description.stride = sizeof(glm::vec4);
      description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }
    else if(vec_data_name[i] == "tex_coord"){
      description.binding = 2;
      description.stride = sizeof(glm::vec2);
      description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }
    else{
      cout<<"[error] data description"<<endl;
      break;
    }

    data_description.push_back(description);
  }

  //---------------------------
  pipeline->info.data_description = data_description;
}
void VK_data::combine_description(Struct_pipeline* pipeline){
  //---------------------------

  VkPipelineVertexInputStateCreateInfo vertex_input_info{};
  vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertex_input_info.vertexBindingDescriptionCount = static_cast<uint32_t>(pipeline->info.data_description.size());
  vertex_input_info.vertexAttributeDescriptionCount = static_cast<uint32_t>(pipeline->info.attribut_description.size());
  vertex_input_info.pVertexBindingDescriptions = pipeline->info.data_description.data();
  vertex_input_info.pVertexAttributeDescriptions = pipeline->info.attribut_description.data();

  //---------------------------
  pipeline->info.vertex_input_info = vertex_input_info;
}
void VK_data::check_for_attribut(Struct_data* data){
  //---------------------------

  if(data->object->rgb.size() != 0){
    data->has_rgb = true;
  }
  if(data->object->uv.size() != 0){
    data->has_uv = true;
  }

  //---------------------------
}
