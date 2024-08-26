#include "Operation.h"

#include <IO/Importer/Namespace.h>
#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace io::imp{

//Constructor / Destructor
Operation::Operation(io::imp::Node* node_importer){
  //---------------------------

  dat::Node* node_data = node_importer->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();
  dat::elm::Node* node_element = node_data->get_node_element();
  eng::Node* node_engine = node_importer->get_node_engine();

  this->io_struct = node_importer->get_io_struct();
  this->dat_entity = node_element->get_dat_entity();
  this->dat_graph = node_graph->get_gph_graph();
  this->dat_set = node_element->get_dat_set();
  this->dat_glyph = node_element->get_dat_glyph();
  this->gph_element = node_graph->get_gph_element();
  this->gph_selection = node_graph->get_gph_selection();
  this->trf_transform = new eng::trf::Transformation();
  this->trf_operation = new eng::trf::Operation();
  this->trf_io = new eng::trf::IO();
  this->atr_field = new dat::atr::Field();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::insert_object(dat::base::Object* object){
  if(object == nullptr) return;
  //---------------------------

  this->ope_clean();
  this->ope_color(object);
  this->ope_transformation(object);
  this->ope_insertion(object);

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
void Operation::ope_clean(){
  //---------------------------

  //Remove old one
  if(io_struct->with_clearing){
    dat::base::Set* set_graph = dat_graph->get_set_graph();
    gph_element->remove_set(set_graph);
  }

  //---------------------------
}
void Operation::ope_color(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  std::vector<float>& vec_I = atr_field->get_field_data(entity->data, "I");

  //If color
  if(entity->data.rgba.size() != 0) return;
  else if(entity->data.rgb.size() != 0){
    entity->data.rgba.resize(entity->data.xyz.size(), glm::vec4(0, 0, 0, 0));

    for(int i=0; i<entity->data.rgb.size(); i++){
      glm::vec3& rgb = entity->data.rgb[i];
      entity->data.rgba[i] = glm::vec4(rgb.x, rgb.y, rgb.z, 1);
    }
  }
  //Else if intensity
  else if(vec_I.size() != 0){
    entity->data.rgba.resize(entity->data.xyz.size(), glm::vec4(0, 0, 0, 0));

    for(int i=0; i<vec_I.size(); i++){
      float& Is = vec_I[i];
      entity->data.rgba[i] = glm::vec4(Is, Is, Is, 1);
    }
  }
  //Else fill with white
  else{
    entity->data.rgba.resize(entity->data.xyz.size(), glm::vec4(0, 0, 0, 0));

    for(int i=0; i<entity->data.xyz.size(); i++){
      entity->data.rgba[i] = glm::vec4(1, 1, 1, 1);
    }
  }

  //---------------------------
}
void Operation::ope_transformation(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Transformation
  trf_io->load_transformation(entity);

  //Scaling
  trf_transform->make_scaling(entity->pose, io_struct->scaling);

  //Centering
  if(io_struct->with_centering){
    trf_operation->center_object(entity);
  }

  //---------------------------
}
void Operation::ope_insertion(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Init object into engine
  if(entity->set_parent == nullptr) entity->set_parent = dat_graph->get_set_graph();
  dat_set->insert_entity(entity->set_parent, entity);
  dat_entity->init_entity(entity);
  dat_glyph->insert_glyph(entity);
  gph_selection->select_element(entity);

  //---------------------------
}

}
