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
  this->atr_field = new dat::atr::field::Manager();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::insert_object(std::shared_ptr<dat::base::Object> object){
  if(object == nullptr) return;
  //---------------------------

  this->ope_clean();
  this->ope_color(object);
  this->ope_transformation(object);
  this->ope_validation(object);
  this->ope_insertion(object);

  //---------------------------
}
void Operation::insert_set(std::shared_ptr<dat::base::Set> set){
  //---------------------------

  std::shared_ptr<dat::base::Set> set_graph = dat_graph->get_set_graph();
  dat_set->add_subset(set_graph, set);
  set->is_locked = true;

  //---------------------------
}

//Subfunction
void Operation::ope_clean(){
  //---------------------------

  //Remove old one
  if(io_struct->operation.with_clearing){
    std::shared_ptr<dat::base::Set> set_graph = dat_graph->get_set_graph();
    gph_element->remove_set(set_graph);
  }

  //---------------------------
}
void Operation::ope_color(std::shared_ptr<dat::base::Object> object){
  if(!object) return;
  //---------------------------

  utl::base::Data& data = *object->data;
  std::unique_lock<std::mutex> lock(data.mutex);

  //Bouger oute cette merde dans colorization dat attribut
  std::vector<float>& vec_I = atr_field->get_field_data(data, "I");

  //If color
  if(data.xyz.size() == 0) return;
  if(data.rgba.size() != 0) return;
  else if(data.rgb.size() != 0){
    data.rgba.resize(data.xyz.size(), glm::vec4(0, 0, 0, 0));

    for(int i=0; i<data.rgb.size(); i++){
      glm::vec3& rgb = data.rgb[i];
      data.rgba[i] = glm::vec4(rgb.x, rgb.y, rgb.z, 1);
    }
  }
  //Else if intensity
  else if(!vec_I.empty()){
    data.rgba.resize(data.xyz.size(), glm::vec4(0, 0, 0, 0));
    std::vector<float> vec_I_n = vec_I;
    math::normalize(vec_I_n);

    for(int i=0; i<vec_I_n.size(); i++){
      float& Is = vec_I_n[i];
      data.rgba[i] = glm::vec4(Is, Is, Is, 1);
    }
  }
  //Else fill with white
  else{
    data.rgba.resize(data.xyz.size(), glm::vec4(0, 0, 0, 0));

    for(int i=0; i<data.xyz.size(); i++){
      data.rgba[i] = glm::vec4(1, 1, 1, 1);
    }
  }

  //---------------------------
}
void Operation::ope_transformation(std::shared_ptr<dat::base::Object> object){
  if(!object) return;
  //---------------------------

  //Transformation
  trf_io->load_transformation(object);

  //Scaling
  trf_transform->make_scaling(*object->pose, io_struct->operation.scaling);

  //Centering
  if(io_struct->operation.with_centering){
    trf_operation->center_object(object);
  }

  //---------------------------
}
void Operation::ope_insertion(std::shared_ptr<dat::base::Object> object){
  if(!object) return;
  //---------------------------

  //Init object into engine
  if(object->set_parent.expired()) object->set_parent = dat_graph->get_set_graph();

  auto parent_set = object->set_parent.lock();
  dat_set->insert_entity(parent_set, object);
  dat_entity->init_entity(*object);
  dat_glyph->insert_glyph(object);
  gph_selection->select_element(object);

  //---------------------------
}
void Operation::ope_validation(std::shared_ptr<dat::base::Object> object){
  if(!object) return;
  //---------------------------

  utl::base::Data& data = *object->data;

  if(data.uv.empty()) data.uv.resize(data.xyz.size(), glm::vec2(0.0f, 0.0f));

  //---------------------------
}

}
