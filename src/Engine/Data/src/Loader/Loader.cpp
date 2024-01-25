#include "Loader.h"

#include <Engine/Engine.h>
#include <Engine/Data/Namespace.h>
#include <Utility/Namespace.h>
//#include <Engine/Capture/K4N/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Loader::Loader(eng::scene::Node* sce_node){
  //---------------------------

  this->engine = sce_node->get_engine();
  this->sce_scene = sce_node->get_scene();
  this->sce_format = new eng::scene::Format();

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

  delete sce_format;

  //---------------------------
}

//Main functions
utl::type::Entity* Loader::load_entity(std::string path){
  utl::type::Entity* entity = nullptr;
  //---------------------------

  //Check file existence
  if(utl::fct::file::is_file_exist(path) == false){
    cout<<"[error] File doesn't exists at "<<path<<endl;
    return nullptr;
  }

  //Check file format
  string format = utl::fct::info::get_format_from_path(path);
  if(!is_format_supported(format)){
    cout<<"[error] File format not supported -> "<<format<<endl;
    return nullptr;
  }

  if(format == "mkv"){
    /*
    eng::capture::Node* node_capture = engine->get_node_capture();
    eng::k4n::Node* k4a_node = node_capture->get_k4a_node();
    eng::k4n::dev::Swarm* k4n_swarm = k4a_node->get_k4n_swarm();

    utl::media::File file;
    file.path_data = path;
    k4n_swarm->create_sensor_playback(file);
    */
  }else{
    entity = load_object(path);
  }

  //---------------------------
  return entity;
}

//Subfunctions
utl::entity::Object* Loader::load_object(string path){
  //---------------------------

  utl::media::File* data = sce_format->get_data_from_file(path);

  utl::entity::Object* object = new utl::entity::Object(engine);
  object->data->path_data = path;
  object->data->file_format = utl::fct::info::get_format_from_path(path);
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

  sce_scene->init_entity(object);

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
