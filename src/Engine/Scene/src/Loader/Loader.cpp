#include "Loader.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Scene/Namespace.h>
#include <Capture/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Loader::Loader(eng::scene::Node* node_scene){
  //---------------------------

  this->sce_param = node_scene->get_scene_param();
  this->node_engine = node_scene->get_node_engine();
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

  entity = load_object(path);

  //---------------------------
  return entity;
}

//Subfunctions
utl::entity::Object* Loader::load_object(string path){
  //---------------------------

  utl::media::File* data = sce_format->import_from_path(path);
  if(data == nullptr) return nullptr;

  utl::entity::Object* object = new utl::entity::Object(node_engine);
  object->data->path_data = path;
  object->data->file_format = utl::fct::info::get_format_from_path(path);
  object->data->has_texture = true;
  object->name = data->name;
  object->data->point.size = data->xyz.size();
  object->data->draw_type = data->draw_type;

  object->data->point.xyz = data->xyz;
  object->data->point.rgb = data->rgb;
  object->data->triangle.uv = data->uv;

  //If no color, fill it with white
  if(object->data->point.rgb.size() == 0){
    for(int i=0; i<data->xyz.size(); i++){
      object->data->point.rgb.push_back(vec4(1,1,1,1));
    }
  }

  //Delete raw data
  delete data;

  sce_scene->init_entity(object);

  //---------------------------
  return object;
}


}
