#include "Manager.h"

#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Scene/Namespace.h>
#include <Data/Namespace.h>
#include <Glyph/Namespace.h>
#include <Loader/Namespace.h>


namespace sce{

//Constructor / Destructor
Manager::Manager(eng::Node* node_engine){
  //---------------------------

  ldr::Node* node_loader = node_engine->get_node_loader();
  vk::Node* node_vulkan = node_engine->get_node_vulkan();
  dat::Node* node_data = node_engine->get_node_data();

  this->node_engine = node_engine;
  this->dat_database = node_data->get_database();
  this->dat_entity = node_data->get_entity();
  this->ldr_loader = node_loader->get_loader();
  this->dat_set = new dat::Set();

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  this->create_glyph_world();

  //---------------------------
}

//Glyph init
void Manager::create_glyph_world(){
  utl::type::Set* set_world = dat_database->get_set_world();
  //---------------------------

  this->create_glyph(set_world, new gly::element::grid::Grid(node_engine));
  this->create_glyph(set_world, new gly::element::world::Axis(node_engine));

  //---------------------------
}
void Manager::create_glyph_object(utl::entity::Object* object){
  //---------------------------

  this->create_glyph(object, new gly::element::object::Axis(node_engine));
  this->create_glyph(object, new gly::element::object::AABB(node_engine));
  this->create_glyph(object, new gly::element::object::Normal(node_engine));

  //---------------------------
}
void Manager::create_glyph_camera(cam::Entity* camera){
  //---------------------------

  this->create_glyph(camera, new cam::glyph::Target(node_engine));

  //---------------------------
}

//Glyph creation
void Manager::create_glyph(utl::type::Set* set, utl::entity::Glyph* glyph){
  //---------------------------

  glyph->create();
  dat_set->insert_entity(set, glyph);

  //---------------------------
}
void Manager::create_glyph(utl::type::Entity* entity, utl::entity::Glyph* glyph){
  //---------------------------

  glyph->create();
  glyph->update_glyph(entity);

  entity->list_glyph.push_back(glyph);

  //---------------------------
}

}
