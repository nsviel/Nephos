#include "Glyph.h"

#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Scene/Namespace.h>
#include <Data/Namespace.h>


namespace dat{

//Constructor / Destructor
Glyph::Glyph(dat::Node* node_data){
  //---------------------------

  eng::Node* node_engine = node_data->get_node_engine();
  ldr::Node* node_loader = node_engine->get_node_loader();
  vk::Node* node_vulkan = node_engine->get_node_vulkan();

  this->node_engine = node_engine;
  this->dat_database = node_data->get_database();
  this->dat_set = new dat::Set();

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
  utl::type::Set* set_world = dat_database->get_set_world();
  //---------------------------

  this->create_glyph(set_world, new dat::glyph::grid::Grid(node_engine));
  this->create_glyph(set_world, new dat::glyph::world::Axis(node_engine));

  //---------------------------
}
void Glyph::create_glyph_object(utl::entity::Object* object){
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
void Glyph::create_glyph(utl::type::Set* set, utl::entity::Glyph* glyph){
  //---------------------------

  glyph->create();
  dat_set->insert_entity(set, glyph);

  //---------------------------
}
void Glyph::create_glyph(utl::type::Entity* entity, utl::entity::Glyph* glyph){
  //---------------------------

  glyph->create();
  glyph->update_glyph(entity);

  entity->list_glyph.push_back(glyph);

  //---------------------------
}

}
