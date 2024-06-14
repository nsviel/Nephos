#include "Transformation.h"

#include <Loader/Namespace.h>


namespace ldr::io{

//Constructor / Destructor
Transformation::Transformation(ldr::Node* node_loader){
  //---------------------------

  this->ldr_struct = node_loader->get_ldr_struct();

  //---------------------------
}
Transformation::~Transformation(){}

//Main function
void Transformation::load_transformation(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  std::string& path = entity->data.path.transformation;
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

  ldr_struct->transformation.path.base = utl::path::get_current_parent_path_abs();
  ldr_struct->transformation.path.folder = utl::path::get_current_parent_path_abs();
  ldr_struct->transformation.path.format = "json";

  //---------------------------
}
void Transformation::update_path(utl::base::Element* element){
  dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element);
  if(entity == nullptr) return;
  //---------------------------

  static dat::base::Entity* old_entity = nullptr;
  if(old_entity != nullptr && entity->UID == old_entity->UID) return;

  std::string& path = entity->data.path.transformation;
  if(path != ""){
    ldr_struct->transformation.path.folder = utl::path::get_dir_from_path(path);
    ldr_struct->transformation.path.name = utl::path::get_name_from_path(path);
    ldr_struct->transformation.path.format = utl::path::get_format_from_path(path);
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
