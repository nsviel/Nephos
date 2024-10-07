#include "Object.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Object::Object(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_buffer = new vk::data::Buffer(vk_struct);
  this->vk_vertex = new vk::data::Vertex(vk_struct);
  this->vk_tex_image = new vk::texture::Image(vk_struct);
  this->vk_command_buffer = new vk::commandbuffer::Pool(vk_struct);
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);
  this->vk_uid = new vk::instance::UID(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);

  //---------------------------
}
Object::~Object(){}

//Main function
void Object::create_object(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose){
  //---------------------------

  //Creat new data struct
  std::shared_ptr<vk::structure::Object> object = std::make_shared<vk::structure::Object>();
  object->data = data;
  object->pose = pose;
  object->UID = vk_uid->query_free_UID();

  //Data
  vk_vertex->build_vertex(*object);

  //Insert data struct into set
  vk_struct->core.data.map_object[data->UID] = object;

  //---------------------------
}
void Object::update_object(vk::structure::Object& object){
  //---------------------------

  //When vertex was empty at object creation, we need to build them now
  if(object.map_vertex.size() == 0){
    vk_vertex->build_vertex(object);
  }else{
    vk_vertex->update_vertex(object);
  }

  //---------------------------
}
void Object::clean_object(std::shared_ptr<vk::structure::Object> object){
  //---------------------------

  //Properly clean object elements
  vk_vertex->clean_vertex(*object);
  vk_tex_image->clean_texture(*object);

  //Remove from data list
  auto it = vk_struct->core.data.map_object.find(object->data->UID);
  if(it != vk_struct->core.data.map_object.end()){
    vk_struct->core.data.map_object.erase(it);
  }

  //---------------------------
}

//Subfunction
std::shared_ptr<vk::structure::Object> Object::retrieve_object(utl::base::Data& data){
  //---------------------------

  auto it = vk_struct->core.data.map_object.find(data.UID);
  if(it == vk_struct->core.data.map_object.end()) return nullptr;

  //---------------------------
  return it->second;
}

}
