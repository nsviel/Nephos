#include "Operation.h"

#include <Core/Namespace.h>
#include <Element/Namespace.h>
#include <IO/Namespace.h>
#include <Utility/Namespace.h>
#include <Graph/Namespace.h>


namespace io::imp{

//Constructor / Destructor
Operation::Operation(io::Node* node_io){
  //---------------------------

  dat::Node* node_data = node_io->get_node_data();
  dat::graph::Node* node_graph = node_data->get_node_graph();

  this->io_struct = node_io->get_io_struct();
  this->io_transformation = node_io->get_io_transformation();
  this->dat_entity = node_data->get_dat_entity();
  this->dat_graph = node_graph->get_dat_graph();
  this->dat_set = node_data->get_dat_set();
  this->dat_glyph = node_data->get_dat_glyph();
  this->dat_selection = node_graph->get_dat_selection();
  this->ope_transform = new ope::Transformation();
  this->ope_operation = new ope::Operation();
  this->utl_attribut = new utl::base::Attribut();

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
  if(io_struct->importer.with_clearing){
    dat::base::Set* set_graph = dat_graph->get_set_graph();
    dat_set->remove_all_entity(set_graph);
  }

  //---------------------------
}
void Operation::ope_color(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  std::vector<float>& vec_I = utl_attribut->get_field_data(&entity->data, "I");

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
  io_transformation->load_transformation(entity);

  //Scaling
  ope_transform->make_scaling(&entity->pose, io_struct->importer.scaling);

  //Centering
  if(io_struct->importer.with_centering){
    ope_operation->center_object(entity);
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
  dat_selection->select_element(entity);

  //---------------------------
}

}
