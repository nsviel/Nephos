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
  this->sce_entity = node_scene->get_scene_entity();
  this->sce_database = node_scene->get_scene_database();
  this->sce_format = node_scene->get_scene_format();
  this->sce_set = new eng::scene::Set();

  //---------------------------
}
Loader::~Loader(){
  //---------------------------

  delete sce_format;

  //---------------------------
}

//Main functions
utl::type::Data* Loader::load_data(string path){
  utl::type::Set* set = nullptr;
  //---------------------------

  if(!check_file_path(path)) return nullptr;

  utl::file::Path utl_path;
  utl_path.data = path;

  //Load data from path
  utl::file::Data* file_data = sce_format->import_from_path(utl_path);
  if(file_data == nullptr) return nullptr;
  if(file_data->type != utl::file::ENTITY) return nullptr;

  utl::type::Data* data = create_data(file_data);

  //Delete raw data
  delete file_data;

  //---------------------------
  return data;
}
utl::type::Set* Loader::load_set(utl::file::Path file_path){
  utl::type::Set* set = nullptr;
  //---------------------------

  if(!check_file_path(file_path.data)) return nullptr;

  //Load data from path
  utl::file::Data* file_data = sce_format->import_from_path(file_path);
  if(file_data == nullptr) return nullptr;
  if(file_data->type != utl::file::SET){
    cout<<"[error] could only load set"<<endl;
    return nullptr;
  }

  //Data is a set
  utl::type::Set* set_scene = sce_database->get_set_scene();
  utl::file::Set* file_set = dynamic_cast<utl::file::Set*>(file_data);
  utl::type::Set* subset = sce_set->get_or_create_subset(set_scene, file_set->name);
  for(int i=0; i<file_set->vec_data.size(); i++){
    utl::entity::Object* object = create_object(file_set->vec_data[i]);
    sce_set->insert_entity(subset, object);
  }

  //Delete raw data
  delete file_data;

  //---------------------------
  return set;
}
utl::entity::Object* Loader::load_object(utl::file::Path file_path){
  //---------------------------

  if(!check_file_path(file_path.data)) return nullptr;

  //Load data from path
  utl::file::Data* file_data = sce_format->import_from_path(file_path);
  if(file_data == nullptr) return nullptr;
  if(file_data->type != utl::file::ENTITY){
    cout<<"[error] could only load entity"<<endl;
    return nullptr;
  }

  //Data is an entity
  utl::type::Set* set_scene = sce_database->get_set_scene();
  utl::file::Entity* file_entity = dynamic_cast<utl::file::Entity*>(file_data);
  utl::entity::Object* object = create_object(file_data);
  sce_set->insert_entity(set_scene, object);

  //Delete raw data
  delete file_data;

  //---------------------------
  return object;
}

//Subfunction
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
    cout<<"[error] '"<<format<<"' file format not supported"<<endl;
    sce_format->display_supported_format();
    return false;
  }

  //---------------------------
  return true;
}
utl::entity::Object* Loader::create_object(utl::file::Data* file_data){
  utl::file::Entity* file_entity = dynamic_cast<utl::file::Entity*>(file_data);
  //---------------------------

  utl::type::Data* data = create_data(file_data);
  utl::entity::Object* object = new utl::entity::Object(node_engine);
  object->name = file_entity->name;
  object->data = *data;

  sce_entity->init_entity(object);

  //---------------------------
  return object;
}
utl::type::Data* Loader::create_data(utl::file::Data* file_data){
  utl::file::Entity* file_entity = dynamic_cast<utl::file::Entity*>(file_data);
  //---------------------------

  utl::type::Data* data = new utl::type::Data();
  data->name = file_entity->name;
  data->path = file_entity->path.data;
  data->file_format = utl::fct::info::get_format_from_path(file_entity->path.data);
  data->size = file_entity->xyz.size();
  data->topology.type = file_entity->draw_type;

  data->xyz = file_entity->xyz;
  data->rgb = file_entity->rgb;
  data->uv = file_entity->uv;

  //If no color, fill it with white
  if(data->rgb.size() == 0){
    for(int i=0; i<file_entity->xyz.size(); i++){
      data->rgb.push_back(vec4(1,1,1,1));
    }
  }

  //---------------------------
  return data;
}

}
