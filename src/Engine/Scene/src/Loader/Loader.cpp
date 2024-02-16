#include "Loader.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Loader::Loader(eng::scene::Node* node_scene){
  //---------------------------

  this->sce_param = node_scene->get_scene_param();
  this->engine = node_scene->get_node_engine();
  this->sce_scene = node_scene->get_scene();
  this->sce_format = node_scene->get_scene_format();

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
  if(!sce_format->is_format_supported(format)){
    cout<<"[error] File format not supported -> "<<format<<endl;
    return nullptr;
  }

  if(format == "mkv"){
    eng::capture::Node* node_capture = engine->get_node_capture();
    k4n::Node* node_k4n = node_capture->get_node_k4n();
    k4n::dev::Swarm* k4n_swarm = node_k4n->get_k4n_swarm();

    utl::media::File file;
    file.path_data = path;
    k4n_swarm->create_sensor_playback(file);
  }else{
    entity = load_object(path);
  }

  //---------------------------
  return entity;
}

//Subfunctions
utl::entity::Object* Loader::load_object(string path){
  //---------------------------

  utl::media::File* data = sce_format->import_data_from_path(path);

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


}
