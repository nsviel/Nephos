#include "Glyph.h"

#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Scene/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Glyph::Glyph(eng::scene::Node* node_scene){
  //---------------------------

  vk::Node* node_vulkan = node_scene->get_node_vulkan();

  this->node_engine = node_scene->get_node_engine();
  this->sce_database = node_scene->get_scene_database();
  this->sce_entity = node_scene->get_scene_entity();
  this->sce_loader = node_scene->get_scene_loader();
  this->sce_set = new eng::scene::Set();

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
  utl::type::Set* set_world = sce_database->get_set_world();
  //---------------------------

  this->create_glyph(set_world, new glyph::grid::Grid(node_engine));
  this->create_glyph(set_world, new glyph::world::Axis(node_engine));

  //---------------------------
}
void Glyph::create_glyph_object(utl::entity::Object* object){
  //---------------------------

  this->create_glyph(object, new glyph::object::Axis(node_engine));
  this->create_glyph(object, new glyph::object::AABB(node_engine));
  this->create_glyph(object, new glyph::object::Normal(node_engine));

  //---------------------------
}
void Glyph::create_glyph_camera(cam::Camera* camera){
  //---------------------------

  this->create_glyph(camera, new cam::glyph::Target(node_engine));

  //---------------------------
}

//Glyph creation
void Glyph::create_glyph(utl::type::Set* set, utl::entity::Glyph* glyph){
  //---------------------------

  glyph->create();
  sce_set->insert_entity(set, glyph);

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
