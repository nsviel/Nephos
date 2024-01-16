#include "Loader.h"
#include "../Format/Format.h"

#include <Engine/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Utility/Base/Namespace.h>
#include <Utility/Function/File/Directory.h>
#include <Utility/Function/File/Zenity.h>
#include <Utility/Function/File/Info.h>
#include <Engine/Capture/K4N/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Loader::Loader(eng::scene::Node* node_scene){
  //---------------------------

  this->engine = node_scene->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->sce_glyph = node_scene->get_scene_glyph();
  this->vk_engine = eng_vulkan->get_vk_engine();

  this->eng_format = new eng::scene::Format();

  this->path_current_dir = "";
  this->supported_format.push_back("pts");
  this->supported_format.push_back("obj");
  this->supported_format.push_back("ply");
  this->supported_format.push_back("xyz");
  this->supported_format.push_back("pcap");
  this->supported_format.push_back("ptx");
  this->supported_format.push_back("csv");
  this->supported_format.push_back("las");
  this->supported_format.push_back("mkv");

  //---------------------------
}
Loader::~Loader(){
  //---------------------------

  delete eng_format;

  //---------------------------
}

//Main functions
entity::Entity* Loader::load_entity(std::string path){
  entity::Entity* entity = nullptr;
  //---------------------------

  //Check file existence
  if(file::is_file_exist(path) == false){
    cout<<"[error] File doesn't exists at "<<path<<endl;
    return nullptr;
  }

  //Check file format
  string format = info::get_format_from_path(path);
  if(!is_format_supported(format)){
    cout<<"[error] File format not supported -> "<<format<<endl;
    return nullptr;
  }

  if(format == "mkv"){
    eng::capture::Node* node_capture = engine->get_node_capture();
    k4n::Node* node_kinect = node_capture->get_node_kinect();
    k4n::Swarm* k4a_swarm = node_kinect->get_k4a_swarm();
    k4a_swarm->create_playback(path);
  }else{
    entity = load_object(path);
  }

  //---------------------------
  return entity;
}

//Subfunctions
entity::Object* Loader::load_object(string path){
  //---------------------------

  utl::base::File* data = eng_format->get_data_from_file(path);

  entity::Object* object = new entity::Object(engine);
  object->data->path_file = path;
  object->data->file_format = info::get_format_from_path(path);
  object->data->has_texture = true;
  object->name = data->name;
  object->data->nb_point = data->xyz.size();
  object->data->draw_type_name = data->draw_type_name;

  object->data->xyz = data->xyz;
  object->data->rgb = data->rgb;
  object->data->uv = data->uv;

  //If no color, fill it with white
  if(object->data->rgb.size() == 0){
    for(int i=0; i<data->xyz.size(); i++){
      object->data->rgb.push_back(vec4(1,1,1,1));
    }
  }

  //Delete raw data
  delete data;

  vk_engine->insert_data_in_engine(object->data);
  sce_glyph->create_glyph_object(object);

  //---------------------------
  return object;
}
bool Loader::is_format_supported(string format){
  //---------------------------

  for(int i=0; i<supported_format.size(); i++){
    if(format == supported_format[i]){
      return true;
    }
  }

  //---------------------------
  return false;
}


}
