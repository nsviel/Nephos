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
  std::string& path = entity->data.path.transformation;
  glm::mat4 mat = utl::transformation::find_transformation_from_file(path);
  element->pose.model = mat;
  element->pose.model_init = mat;

  //---------------------------
}
void Transformation::save_transformation(utl::base::Element* element, std::string path){
  //---------------------------



  //---------------------------
}

//Subfunction
std::vector<std::string> Transformation::get_supported_format(){
  std::vector<std::string> vec_format;
  //---------------------------

  vec_format.push_back("json");

  //---------------------------
  return vec_format;
}

}
