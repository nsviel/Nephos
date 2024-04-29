#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Scene/Namespace.h>
#include <Scene/Namespace.h>
#include <Glyph/Namespace.h>


namespace gly{

//Constructor / Destructor
Node::Node(sce::Node* node_scene){
  //---------------------------

  vk::Node* node_vulkan = node_scene->get_node_vulkan();

  this->node_engine = node_scene->get_node_engine();
  this->dat_database = node_scene->get_scene_database();
  this->dat_entity = node_scene->get_scene_entity();
  this->ldr_loader = node_scene->get_scene_loader();
  this->sce_set = new dat::Set();

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  this->create_glyph_world();

  //---------------------------
}

//Glyph init
void Node::create_glyph_world(){
  utl::type::Set* set_world = dat_database->get_set_world();
  //---------------------------

  this->create_glyph(set_world, new gly::element::grid::Grid(node_engine));
  this->create_glyph(set_world, new gly::element::world::Axis(node_engine));

  //---------------------------
}
void Node::create_glyph_object(utl::entity::Object* object){
  //---------------------------

  this->create_glyph(object, new gly::element::object::Axis(node_engine));
  this->create_glyph(object, new gly::element::object::AABB(node_engine));
  this->create_glyph(object, new gly::element::object::Normal(node_engine));

  //---------------------------
}
void Node::create_glyph_camera(cam::Entity* camera){
  //---------------------------

  this->create_glyph(camera, new cam::glyph::Target(node_engine));

  //---------------------------
}

//Glyph creation
void Node::create_glyph(utl::type::Set* set, utl::entity::Glyph* glyph){
  //---------------------------

  glyph->create();
  sce_set->insert_entity(set, glyph);

  //---------------------------
}
void Node::create_glyph(utl::type::Entity* entity, utl::entity::Glyph* glyph){
  //---------------------------

  glyph->create();
  glyph->update_glyph(entity);

  entity->list_glyph.push_back(glyph);

  //---------------------------
}

}
