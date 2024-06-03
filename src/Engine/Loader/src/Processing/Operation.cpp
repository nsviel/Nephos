#include "Operation.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Utility/Namespace.h>


namespace ldr::processing{

//Constructor / Destructor
Operation::Operation(ldr::Node* node_loader){
  //---------------------------

  dat::Node* node_data = node_loader->get_node_data();

  this->dat_entity = node_data->get_dat_entity();
  this->dat_graph = node_data->get_dat_graph();
  this->dat_set = node_data->get_dat_set();
  this->dat_glyph = node_data->get_dat_glyph();

  //---------------------------
}
Operation::~Operation(){}

//Main functions
void Operation::insert_object(dat::base::Object* object){
  if(object == nullptr) return;
  //---------------------------

  //If no color, fill it with white
  if(object->data.rgb.size() == 0){
    for(int i=0; i<object->data.xyz.size(); i++){
      object->data.rgba.push_back(vec4(1, 1, 1, 1));
    }
  }else{
    for(int i=0; i<object->data.rgb.size(); i++){
      glm::vec3& rgb = object->data.rgb[i];
      object->data.rgba.push_back(vec4(rgb.x, rgb.y, rgb.z, 1));
    }
  }

  //Transformation
  this->transformation_from_file(object);

  //Init object into engine
  dat::base::Set* set_graph = dat_graph->get_set_graph();
  dat_set->insert_entity(set_graph, object);
  dat_entity->init_entity(object);
  dat_glyph->insert_glyph(object);

  //---------------------------
}
void Operation::insert_set(dat::base::Set* set){
  if(set == nullptr) return;
  //---------------------------

  dat::base::Set* set_graph = dat_graph->get_set_graph();
  dat_set->add_subset(set_graph, set);
  set->is_locked = true;

  //---------------------------
}

//Subfunction
void Operation::transformation_from_file(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Transformation
  std::string& path = entity->data.path.transformation;
  glm::mat4 mat = utl::transformation::find_transformation_from_file(path);
  entity->pose.model = mat;
  entity->pose.model_init = mat;

  //---------------------------
}

}
