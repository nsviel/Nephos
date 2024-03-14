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
  this->vk_graphical = node_vulkan->get_vk_graphical();
  this->sce_database = node_scene->get_scene_database();
  this->sce_entity = node_scene->get_scene_entity();
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

//Glyph function
void Glyph::create_glyph_world(){
  utl::type::Set* set_world = sce_database->get_set_world();
  //---------------------------

  this->create_glyph(set_world, new glyph::grid::Grid(node_engine));
  this->create_glyph(set_world, new glyph::world::Axis(node_engine));

  //---------------------------
}
void Glyph::create_glyph_object(utl::entity::Object* object){
  //---------------------------




  if(object->list_glyph.size() != 0) return;
  object->list_glyph.push_back(new glyph::object::Axis(node_engine));
  object->list_glyph.push_back(new glyph::object::AABB(node_engine));
  object->list_glyph.push_back(new glyph::object::Normal(node_engine));

  for(int i=0; i<object->list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(object->list_glyph.begin(), i);

    glyph->create();
    sce_entity->init_entity(glyph);
  }

  //---------------------------
}
void Glyph::create_glyph_camera(utl::entity::Camera* camera){
  //---------------------------

  if(camera->list_glyph.size() != 0) return;
  camera->list_glyph.push_back(new glyph::camera::Target(node_engine));

  for(int i=0; i<camera->list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(camera->list_glyph.begin(), i);

    //Glyph creation
    glyph->create();
    glyph->update_glyph(camera);
    sce_entity->init_entity(glyph);
  }

  //---------------------------
}

//Subfunction
void Glyph::create_glyph(utl::type::Set* set, utl::entity::Glyph* glyph){
  //---------------------------

  glyph->create();
  sce_set->insert_entity(set, glyph);
  sce_entity->init_entity(glyph);

  //---------------------------
}
void Glyph::create_glyph(utl::type::Entity* entity, utl::entity::Glyph* glyph){
  //---------------------------

  glyph->create();
  sce_entity->init_entity(glyph);
  entity->list_glyph.push_back(glyph);

  //---------------------------
}

}
