#include "Data.h"

#include <Vulkan/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Data::Data(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_buffer = new Buffer(struct_vulkan);
  this->vk_texture = new vk::main::VK_texture(struct_vulkan);
  this->vk_command = new vk::command::Command(struct_vulkan);
  this->vk_descriptor = new vk::binding::Descriptor(struct_vulkan);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::insert_data(utl::type::Data* data, utl::type::Pose* pose){
  //---------------------------

  //Creat new data struct
  vk::structure::Object* vk_object = new vk::structure::Object();
  vk_object->data = data;
  vk_object->pose = pose;

  //Descriptor
  descriptor_required mvp = std::make_tuple("mvp", sizeof(mat4), 0, TYP_UNIFORM, TYP_SHADER_VS);
  vk_object->binding.vec_required_binding.push_back(mvp);

  if(data->draw_type_name == "point"){
    descriptor_required size = std::make_tuple("point_size", sizeof(int), 1, TYP_UNIFORM, TYP_SHADER_VS);
    vk_object->binding.vec_required_binding.push_back(size);
  }

  //Apply adequat init functions
  vk_buffer->create_buffers(vk_object);
  vk_command->allocate_command_buffer_secondary(vk_object);
  vk_descriptor->create_layout_from_required(&vk_object->binding);
  vk_descriptor->create_binding(&vk_object->binding);

  //Insert data struct into set
  struct_vulkan->data.list_vk_object.push_back(vk_object);

  //---------------------------
}
void Data::update_data(utl::type::Data* data, vk::structure::Object* vk_object){
  //---------------------------

  vk_object->data = data;
  vk_buffer->clean_buffers(vk_object);
  vk_buffer->create_buffers(vk_object);

  //---------------------------
}
void Data::clean(){
  //---------------------------

  for(int i=0; i<struct_vulkan->data.list_vk_object.size(); i++){
    vk::structure::Object* data = *next(struct_vulkan->data.list_vk_object.begin(),i);
    this->clean_vk_object(data);
  }

  //---------------------------
}
void Data::clean_vk_object(vk::structure::Object* vk_object){
  //---------------------------

  vkDeviceWaitIdle(struct_vulkan->device.device);

  vk_buffer->clean_buffers(vk_object);
  vk_texture->clean_texture(vk_object);
  vk_descriptor->clean_binding(&vk_object->binding);

  //---------------------------
}

//Data description
void Data::pipeline_data_description(vk::structure::Pipeline* pipeline){
  //---------------------------

  this->pipeline_binding_description(pipeline);
  this->pipeline_attribut_description(pipeline);
  this->pipeline_vertex_input_info(pipeline);

  //---------------------------
}
void Data::pipeline_attribut_description(vk::structure::Pipeline* pipeline){
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
      attribut.location = 4;
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
void Data::pipeline_binding_description(vk::structure::Pipeline* pipeline){
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
void Data::pipeline_vertex_input_info(vk::structure::Pipeline* pipeline){
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

}
