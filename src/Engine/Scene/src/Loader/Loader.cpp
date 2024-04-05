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

  //Init
  if(!check_file_path(path)) return nullptr;
  utl::Path utl_path;
  utl_path.data = path;

  //Load data from path
  utl::File* file = sce_format->import_from_path(utl_path);
  if(file == nullptr || file->type != utl::file::DATA) return nullptr;
  utl::file::Data* file_data = dynamic_cast<utl::file::Data*>(file);

  utl::type::Data* data = create_data(file_data);

  //Delete raw data
  delete file;

  //---------------------------
  return data;
}
utl::type::Set* Loader::load_dataset(utl::Path file_path){
  //---------------------------

  if(!check_file_path(file_path.data)) return nullptr;

  //Load data from path
  utl::File* file = sce_format->import_from_path(file_path);
  if(file == nullptr || file->type != utl::file::DATASET) return nullptr;
  utl::file::Dataset* dataset = dynamic_cast<utl::file::Dataset*>(file);

  //Insert loaded set into scene
  utl::type::Set* set_scene = sce_database->get_set_scene();
  utl::type::Set* set = sce_set->get_or_create_subset(set_scene, dataset->name);
  set->is_locked = true;

  //Insert all set objects into engine
  for(int i=0; i<dataset->vec_data.size(); i++){
    utl::entity::Object* object = create_object(dataset->vec_data[i]);
    sce_set->insert_entity(set, object);
  }

  //Delete raw data
  delete file;

  sce_format->insert_from_path(file_path, set);

  //---------------------------
  return set;
}
utl::entity::Object* Loader::load_object(utl::Path file_path){
  //---------------------------

  if(!check_file_path(file_path.data)) return nullptr;

  //Load data from path
  utl::File* file = sce_format->import_from_path(file_path);
  if(file == nullptr || file->type != utl::file::DATA) return nullptr;
  utl::file::Data* file_data = dynamic_cast<utl::file::Data*>(file);

  //Data is an entity
  utl::type::Set* set_scene = sce_database->get_set_scene();
  utl::entity::Object* object = create_object(file_data);
  sce_set->insert_entity(set_scene, object);

  //Delete raw data
  delete file;

  //---------------------------
  return object;
}

//Subfunction
bool Loader::check_file_path(std::string path){
  //---------------------------

  //Check file existence
  if(utl::file::is_exist(path) == false){
    cout<<"[error] File doesn't exists at "<<path<<endl;
    return false;
  }

  //Check file format
  string format = utl::path::get_format_from_path(path);
  if(!sce_format->is_format_supported(format)){
    cout<<"[error] '"<<format<<"' file format not supported"<<endl;
    sce_format->display_supported_format();
    return false;
  }

  //---------------------------
  return true;
}
utl::entity::Object* Loader::create_object(utl::file::Data* data){
  //---------------------------

  utl::entity::Object* object = new utl::entity::Object(node_engine);
  object->name = data->name;
  object->data = *create_data(data);

  sce_entity->init_entity(object);

  //---------------------------
  return object;
}
utl::type::Data* Loader::create_data(utl::file::Data* file){
  //---------------------------

  utl::type::Data* data = new utl::type::Data();
  data->name = file->name;
  data->path = file->path.data;
  data->file_format = utl::path::get_format_from_path(file->path.data);
  data->size = file->xyz.size();
  data->topology.type = file->draw_type;

  data->xyz = file->xyz;
  data->rgb = file->rgb;
  data->uv = file->uv;

  //If no color, fill it with white
  if(data->rgb.size() == 0){
    for(int i=0; i<file->xyz.size(); i++){
      data->rgb.push_back(vec4(1,1,1,1));
    }
  }

  //---------------------------
  return data;
}

}
