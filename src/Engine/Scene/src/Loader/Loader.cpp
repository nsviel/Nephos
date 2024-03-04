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
utl::type::Set* Loader::load_data(utl::file::Path path){
  utl::type::Set* set = nullptr;
  //---------------------------

  if(!check_file_path(path.data)) return nullptr;

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

//Data function
utl::type::Set* Loader::load_object(utl::file::Data* data){
  //---------------------------

  utl::type::Set* set_scene = sce_database->get_set_scene();
  utl::entity::Object* object = create_object(data);

  sce_set->insert_entity(set_scene, object);

  //---------------------------
  return set_scene;
}
utl::type::Set* Loader::load_set(utl::file::Data* data){
  utl::file::Set* set = dynamic_cast<utl::file::Set*>(data);
  //---------------------------

  utl::type::Set* set_scene = sce_database->get_set_scene();
  utl::type::Set* subset = sce_set->get_or_create_subset(set_scene, set->name);

  for(int i=0; i<set->vec_data.size(); i++){
    utl::entity::Object* object = create_object(set->vec_data[i]);
    sce_set->insert_entity(subset, object);
  }

  //---------------------------
  return subset;
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
utl::entity::Object* Loader::create_object(utl::file::Data* data){
  utl::file::Entity* entity = dynamic_cast<utl::file::Entity*>(data);
  //---------------------------

  utl::entity::Object* object = new utl::entity::Object(node_engine);
  object->data->path = entity->path.data;
  object->data->file_format = utl::fct::info::get_format_from_path(entity->path.data);
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

  sce_entity->init_entity(object);

  //---------------------------
  return object;
}

}
