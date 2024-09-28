#include "Object.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Object::Object(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_buffer = new vk::data::Buffer(vk_struct);
  this->vk_texture = new vk::texture::Data(vk_struct);
  this->vk_command_buffer = new vk::command::Command_buffer(vk_struct);
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);
  this->vk_uid = new vk::instance::UID(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);

  //---------------------------
}
Object::~Object(){}

//Main function
void Object::update_object(vk::structure::Object& object){
  //---------------------------

  //sometimes at data init the data size is 0, the nbuffers are not created so we need to create them now
  if(object.buffer.xyz.data.mem == 0){
    vk_buffer->create_buffer(object);
  }else{
    vk_buffer->update_buffer(object);
  }

  //---------------------------
}
void Object::create_object(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose){
  //---------------------------

  //Creat new data struct
  std::shared_ptr<vk::structure::Object> object = std::make_shared<vk::structure::Object>();
  object->data = data;
  object->pose = pose;
  object->UID = vk_uid->query_free_UID();

  //Data
  vk_buffer->create_buffer(*object);

  //Texture
  for(auto& [name, image] : data->map_image){
    vk_texture->insert_texture(*object, image);
  }

  //Descriptor
  std::shared_ptr<vk::structure::Pipeline> pipeline = vk_struct->core.pipeline.map_topology[object->data->topology.type];
  vk_descriptor_set->allocate_descriptor_set(object->descriptor_set, pipeline->descriptor.layout);

  //Insert data struct into set
  vk_struct->core.data.map_object[data->UID] = object;

  //---------------------------
}
void Object::clean_object(std::shared_ptr<vk::structure::Object> object){
  //---------------------------

  //Properly clean object elements
  vk_buffer->clean_buffers(*object);
  vk_texture->clean_texture(*object);
  vk_descriptor_set->clean_descriptor_set(object->descriptor_set);

  //Remove from data list
  auto it = vk_struct->core.data.map_object.find(object->data->UID);
  if (it != vk_struct->core.data.map_object.end()){
    vk_struct->core.data.map_object.erase(it);
  }

  //---------------------------
}
std::shared_ptr<vk::structure::Object> Object::retrieve_object(utl::base::Data& data){
  //---------------------------

  auto it = vk_struct->core.data.map_object.find(data.UID);
  if(it == vk_struct->core.data.map_object.end()) return nullptr;

  //---------------------------
  return it->second;
}

}
