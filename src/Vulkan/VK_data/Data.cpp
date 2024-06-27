#include "Data.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Data::Data(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_buffer = new vk::data::Buffer(vk_struct);
  this->vk_texture = new vk::image::Texture(vk_struct);
  this->vk_command_buffer = new vk::command::Command_buffer(vk_struct);
  this->vk_descriptor = new vk::binding::Descriptor(vk_struct);
  this->vk_uid = new vk::instance::UID(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);
  this->vk_uniform = new vk::binding::Uniform(vk_struct);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::clean(){
  std::list<vk::structure::Object*>& list_vk_object = vk_struct->data.list_vk_object;
  //---------------------------

  auto it = list_vk_object.begin();
  while(it != list_vk_object.end()){
    this->clean_vk_object(*it);
    it = list_vk_object.begin();
  }

  //---------------------------
}

//Data function
void Data::insert_data(utl::base::Data* data, utl::base::Pose* pose){
  //---------------------------

  //Creat new data struct
  vk::structure::Object* vk_object = new vk::structure::Object();
  vk_object->data = data;
  vk_object->pose = pose;
  vk_object->UID = vk_uid->query_free_UID();

  //Descriptor
  vk::structure::Descriptor_required descriptor = vk_uniform->uniform_mvp();
  vk_object->binding.vec_required_binding.push_back(descriptor);

  if(data->topology.type == utl::topology::POINT){
    vk::structure::Descriptor_required descriptor = vk_uniform->uniform_point_size();
    vk_object->binding.vec_required_binding.push_back(descriptor);
  }

  //Apply adequat init functions
  this->check_data(vk_object);
  vk_buffer->create_buffers(vk_object);
  vk_descriptor->create_layout_from_required(&vk_object->binding);
  vk_descriptor->create_binding(&vk_object->binding);

  //Insert data struct into set
  vk_struct->data.list_vk_object.push_back(vk_object);

  //---------------------------
}
void Data::update_data(utl::base::Data* data, vk::structure::Object* vk_object){
    //---------------------------

    vk_object->data = data;
    this->check_data(vk_object);

    //sometimes at data init the data size is 0, the nbuffers are not created so we need to create them now
    if(vk_object->buffer.xyz.mem == 0){
      vk_buffer->create_buffers(vk_object);
    }else{
      vk_buffer->update_buffer(vk_object);
    }

    //---------------------------
}
void Data::clean_vk_object(vk::structure::Object* vk_object){
  std::list<vk::structure::Object*>& list_vk_object = vk_struct->data.list_vk_object;
  //---------------------------

  vk_synchro->wait_idle_and_pause();
  vk_buffer->clean_buffers(vk_object);
  vk_texture->clean_texture(vk_object);
  vk_descriptor->clean_binding(&vk_object->binding);
  list_vk_object.remove(vk_object);
  vk_synchro->end_idle();

  //---------------------------
}
void Data::check_data(vk::structure::Object* vk_object){
  utl::base::Data* data = vk_object->data;
  //---------------------------

  vk_object->has_xyz = (data->xyz.size() == 0) ? false : true;
  vk_object->has_rgba = (data->rgba.size() == 0) ? false : true;
  vk_object->has_uv =  (data->uv.size()  == 0) ? false : true;

  //---------------------------
}

}
