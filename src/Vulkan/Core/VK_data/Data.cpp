#include "Data.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Data::Data(vk::Structure* vk_struct){
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
Data::~Data(){}

//Main function
void Data::insert(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose){
  //---------------------------

  //Check if data already in engine
  auto it = vk_struct->core.data.map_vk_object.find(data->UID);
  if(it != vk_struct->core.data.map_vk_object.end()){
    this->update_vk_object(data, *it->second);
    return;
  }

  //If not, insert it
  this->create_vk_object(data, pose);

  //---------------------------
}
void Data::remove(utl::base::Data& data){
  //---------------------------

  //Search for vk object to remove
  auto it = vk_struct->core.data.map_vk_object.find(data.UID);
  if(it != vk_struct->core.data.map_vk_object.end()){
    this->clean_vk_object(it->second);
  }

  //---------------------------
}
void Data::clean(){
  //---------------------------

  auto it = vk_struct->core.data.map_vk_object.begin();
  while(it != vk_struct->core.data.map_vk_object.end()){
    this->clean_vk_object(it->second);
    it = vk_struct->core.data.map_vk_object.begin();
  }

  //---------------------------
}

//Subfunction
void Data::update_vk_object(std::shared_ptr<utl::base::Data> data, vk::structure::Object& vk_object){
  //---------------------------

  //sometimes at data init the data size is 0, the nbuffers are not created so we need to create them now
  if(vk_object.buffer.xyz.data.mem == 0){
    vk_buffer->create_buffer(vk_object);
  }else{
    vk_buffer->update_buffer(vk_object);
  }

  //---------------------------
}
void Data::create_vk_object(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose){
  //---------------------------

  //Creat new data struct
  std::shared_ptr<vk::structure::Object> vk_object = std::make_shared<vk::structure::Object>();
  vk_object->data = data;
  vk_object->pose = pose;
  vk_object->UID = vk_uid->query_free_UID();

  //Data
  vk_buffer->create_buffer(*vk_object);
  //vk_texture->insert_texture(std::make_shared<utl::media::Image>(data->texture));

  //Descriptor
  this->descriptor_vk_object(*vk_object);

  //Insert data struct into set
  vk_struct->core.data.map_vk_object[data->UID] = vk_object;

  //---------------------------
}
void Data::clean_vk_object(std::shared_ptr<vk::structure::Object> vk_object){
  //---------------------------

  //Properly clean object elements
  vk_buffer->clean_buffers(*vk_object);
  vk_texture->clean_texture(*vk_object);
  vk_descriptor_set->clean_descriptor_set(vk_object->descriptor_set);

  //Remove from data list
  auto it = vk_struct->core.data.map_vk_object.find(vk_object->data->UID);
  if (it != vk_struct->core.data.map_vk_object.end()) {
    vk_struct->core.data.map_vk_object.erase(it);
  }

  //---------------------------
}
void Data::descriptor_vk_object(vk::structure::Object& vk_object){
  //---------------------------

  std::shared_ptr<vk::structure::Pipeline> pipeline = vk_struct->core.pipeline.map[vk_object.data->topology.type];
  vk_descriptor_set->allocate_descriptor_set(vk_object.descriptor_set, pipeline->descriptor.layout);

  //---------------------------
}

}
