#include "IO.h"

#include <Engine/Transformation/Namespace.h>
#include <Utility/Namespace.h>
#include <Element/Namespace.h>


namespace eng::trf{

//Constructor / Destructor
IO::IO(){
  //---------------------------

  this->trf_utils = new eng::trf::Utils();

  //---------------------------
}
IO::~IO(){}

//Main function
void IO::load_transformation(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  std::string path = entity->pose.path.build();
  this->load_transformation(entity, path);

  //---------------------------
}
void IO::load_transformation(utl::base::Element* element, std::string path){
  //---------------------------

  //Transformation
  glm::mat4 mat = trf_utils->find_transformation_from_file(path);

  if(mat != glm::mat4(1)){
    element->pose.model = mat;
    element->pose.model_init = mat;
  }

  //---------------------------
}
void IO::save_transformation(utl::base::Element* element, std::string path){
  //---------------------------

  glm::mat4& mat = element->pose.model;
  trf_utils->save_transformation_to_file(mat, path);

  //---------------------------
}

//Subfunction
void IO::init_path(){
  //---------------------------

  this->path.directory = utl::path::get_current_directory_path();
  this->path.format = ".json";

  //---------------------------
}
void IO::update_path(utl::base::Element* element){
  dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element);
  if(entity == nullptr) return;
  //---------------------------

  static dat::base::Entity* old_entity = nullptr;
  if(old_entity != nullptr && entity->UID == old_entity->UID) return;

  std::string path = entity->pose.path.build();
  if(path != ""){
    this->path.directory = utl::path::get_dir_from_path(path);
    this->path.name = utl::path::get_name_from_path(path);
    this->path.format = utl::path::get_format_from_path(path);
    old_entity = entity;
  }

  //---------------------------
}
std::vector<std::string> IO::get_supported_format(){
  std::vector<std::string> vec_format;
  //---------------------------

  vec_format.push_back("json");

  //---------------------------
  return vec_format;
}

}
