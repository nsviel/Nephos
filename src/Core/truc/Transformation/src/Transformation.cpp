#include "Transformation.h"

#include <IO/Namespace.h>


namespace io::trf{

//Constructor / Destructor
Transformation::Transformation(io::trf::Node* node_transfo){
  //---------------------------

  this->io_struct = node_transfo->get_io_struct();

  //---------------------------
}
Transformation::~Transformation(){}

//Main function
void Transformation::load_transformation(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  std::string path = entity->pose.path.build();
  this->load_transformation(entity, path);

  //---------------------------
}
void Transformation::load_transformation(utl::base::Element* element, std::string path){
  //---------------------------

  //Transformation
  glm::mat4 mat = utl::transformation::find_transformation_from_file(path);

  if(mat != glm::mat4(1)){
    element->pose.model = mat;
    element->pose.model_init = mat;
  }

  //---------------------------
}
void Transformation::save_transformation(utl::base::Element* element, std::string path){
  //---------------------------

  glm::mat4& mat = element->pose.model;
  utl::transformation::save_transformation_to_file(mat, path);

  //---------------------------
}

//Subfunction
void Transformation::init_path(){
  //---------------------------

  io_struct->path.directory = utl::path::get_current_directory_path();
  io_struct->path.format = ".json";

  //---------------------------
}
void Transformation::update_path(utl::base::Element* element){
  dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element);
  if(entity == nullptr) return;
  //---------------------------

  static dat::base::Entity* old_entity = nullptr;
  if(old_entity != nullptr && entity->UID == old_entity->UID) return;

  std::string path = entity->pose.path.build();
  if(path != ""){
    io_struct->path.directory = utl::path::get_dir_from_path(path);
    io_struct->path.name = utl::path::get_name_from_path(path);
    io_struct->path.format = utl::path::get_format_from_path(path);
    old_entity = entity;
  }

  //---------------------------
}
std::vector<std::string> Transformation::get_supported_format(){
  std::vector<std::string> vec_format;
  //---------------------------

  vec_format.push_back("json");

  //---------------------------
  return vec_format;
}

}
