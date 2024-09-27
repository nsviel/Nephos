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
  this->vk_object = new vk::data::Object(vk_struct);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::insert(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose){
  //---------------------------

  //Check if data already in engine
  auto it = vk_struct->core.data.map_object.find(data->UID);
  if(it != vk_struct->core.data.map_object.end()){
    vk_object->update_object(data, *it->second);
    return;
  }

  //If not, insert it
  vk_object->create_object(data, pose);

  //---------------------------
}
void Data::remove(utl::base::Data& data){
  //---------------------------

  //Search for vk object to remove
  auto it = vk_struct->core.data.map_object.find(data.UID);
  if(it != vk_struct->core.data.map_object.end()){
    vk_object->clean_object(it->second);
  }

  //---------------------------
}
void Data::clean(){
  //---------------------------

  auto it = vk_struct->core.data.map_object.begin();
  while(it != vk_struct->core.data.map_object.end()){
    vk_object->clean_object(it->second);
    it = vk_struct->core.data.map_object.begin();
  }

  //---------------------------
}

//Subfunction

}
