#include "Data.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Data::Data(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_object = new vk::data::Object(vk_struct);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::insert(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose){
  //---------------------------

  //Check if data already in engine
  if(is_present(data)){
    this->update(data);
  }
  //If not, create it
  else{
    vk_object->create_object(data, pose);
  }

  //---------------------------
}
void Data::update(std::shared_ptr<utl::base::Data> data){
  //---------------------------

  //Check if data already in engine
  auto it = vk_struct->core.data.map_object.find(data->UID);
  if(it != vk_struct->core.data.map_object.end()){
    vk_object->update_object(*it->second);
    return;
  }

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
bool Data::is_present(std::shared_ptr<utl::base::Data> data){
  //---------------------------

  //Check if data already in engine
  auto it = vk_struct->core.data.map_object.find(data->UID);
  if(it != vk_struct->core.data.map_object.end()){
    return true;
  }

  //---------------------------
  return false;
}

}
