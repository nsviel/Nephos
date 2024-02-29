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
utl::type::Set* Loader::load_data(std::string path){
  utl::type::Set* set = nullptr;
  //---------------------------

  if(!check_file_path(path)) return nullptr;

  //Load data from path
  utl::file::Data* data = sce_format->import_from_path(path);
  if(data == nullptr) return nullptr;

  //Data is an entity
  switch(data->type){
    case utl::file::ENTITY:{
      set = load_object(data);
      break;
    }
    case utl::file::SET:{
      set = load_set(data);
      break;
    }
  }

  //Delete raw data
  delete data;

  //---------------------------
  return set;
}

//Subfunctions
bool Loader::check_file_path(std::string path){
  //---------------------------

  //Check file existence
  if(utl::fct::file::is_file_exist(path) == false){
    cout<<"[error] File doesn't exists at "<<path<<endl;
    return false;
  }

  //Check file format
  string format = utl::fct::info::get_format_from_path(path);
  if(!sce_format->is_format_supported(format)){
    cout<<"[error] File format not supported -> "<<format<<endl;
    return false;
  }

  //---------------------------
  return true;
}
utl::type::Set* Loader::load_object(utl::file::Data* data){
  utl::file::Entity* entity = dynamic_cast<utl::file::Entity*>(data);
  //---------------------------

  utl::type::Set* set_scene = sce_scene->get_set_scene();

  //Data is an entity
  utl::entity::Object* object = new utl::entity::Object(node_engine);
  object->data->path = entity->path;
  object->data->file_format = utl::fct::info::get_format_from_path(entity->path);
  object->data->has_texture = true;
  object->name = entity->name;
  object->data->point.size = entity->xyz.size();
  object->data->draw_type = entity->draw_type;

  object->data->point.xyz = entity->xyz;
  object->data->point.rgb = entity->rgb;
  object->data->triangle.uv = entity->uv;

  //If no color, fill it with white
  if(object->data->point.rgb.size() == 0){
    for(int i=0; i<entity->xyz.size(); i++){
      object->data->point.rgb.push_back(vec4(1,1,1,1));
    }
  }

  set_scene->insert_entity(object);
  set_scene->set_selected_entity(object);
  sce_scene->init_entity(object);

  //---------------------------
  return set_scene;
}
utl::type::Set* Loader::load_set(utl::file::Data* data){
  utl::file::Set* set = dynamic_cast<utl::file::Set*>(data);
  //---------------------------




  //---------------------------
}


}
