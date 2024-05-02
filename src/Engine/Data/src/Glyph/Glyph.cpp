#include "Glyph.h"

#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Data/Namespace.h>


namespace dat{

//Constructor / Destructor
Glyph::Glyph(dat::Node* node_data){
  //---------------------------

  eng::Node* node_engine = node_data->get_node_engine();
  vk::Node* node_vulkan = node_engine->get_node_vulkan();

  this->node_engine = node_engine;
  this->dat_graph = node_data->get_data_graph();
  this->dat_set = node_data->get_set();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::init(){
  //---------------------------

  this->create_glyph_world();

  //---------------------------
}

//Glyph init
void Glyph::create_glyph_world(){
  dat::base::Set* set_world = dat_graph->get_set_scene();
  //---------------------------

  this->create_glyph(set_world, new dat::glyph::grid::Grid(node_engine));
  this->create_glyph(set_world, new dat::glyph::world::Axis(node_engine));

  //---------------------------
}
void Glyph::create_glyph_object(dat::base::Object* object){
  //---------------------------

  this->create_glyph(object, new dat::glyph::object::Axis(node_engine));
  this->create_glyph(object, new dat::glyph::object::AABB(node_engine));
  this->create_glyph(object, new dat::glyph::object::Normal(node_engine));

  //---------------------------
}
void Glyph::create_glyph_camera(cam::Entity* camera){
  //---------------------------

  this->create_glyph(camera, new cam::glyph::Target(node_engine));

  //---------------------------
}

//Glyph creation
void Glyph::create_glyph(dat::base::Set* set, dat::base::Glyph* glyph){
  //---------------------------

  glyph->create();
  dat_set->insert_entity(set, glyph);

  //---------------------------
}
void Glyph::create_glyph(dat::base::Entity* entity, dat::base::Glyph* glyph){
  //---------------------------

  glyph->create();
  glyph->update_glyph(entity);

  entity->list_glyph.push_back(glyph);

  //---------------------------
}

}
