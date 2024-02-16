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
  this->sce_world = node_scene->get_scene_world();

  //---------------------------
}
Glyph::~Glyph(){
  //---------------------------

  this->remove_glyph_world();

  //---------------------------
}

//Glyph world
void Glyph::create_glyph_world(){
  utl::type::Set* data_set = sce_database->get_data_set();
  utl::type::Set* set_world = data_set->get_set("World");
  //---------------------------

  vector<utl::entity::Glyph*> vec_glyph;
  vec_glyph.push_back(new glyph::grid::Grid(node_engine));
  vec_glyph.push_back(new glyph::world::Axis(node_engine));

  for(int i=0; i<vec_glyph.size(); i++){
    utl::entity::Glyph* glyph = vec_glyph[i];

    glyph->create();
    sce_world->import_entity(glyph);
  }

  //---------------------------
}
void Glyph::remove_glyph_world(){
  utl::type::Set* data_set = sce_database->get_data_set();
  utl::type::Set* set_world = data_set->get_set("World");
  //---------------------------

  for(int i=0; i<set_world->list_entity.size(); i++){
    utl::entity::Glyph* glyph = (utl::entity::Glyph*)*next(set_world->list_entity.begin(), i);

    vector<utl::type::Data*> vec_data = glyph->get_vec_data();
    for(int j=0; j<vec_data.size(); j++){
      vk_graphical->remove_data_in_engine(vec_data[j]);
    }

    delete glyph;
  }

  //---------------------------
  set_world->list_entity.clear();
}

//Glyph object
void Glyph::create_glyph_object(utl::entity::Object* object){
  //---------------------------

  if(object->list_glyph.size() != 0) return;
  object->list_glyph.push_back(new glyph::object::Axis(node_engine));
  object->list_glyph.push_back(new glyph::object::AABB(node_engine));

  for(int i=0; i<object->list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(object->list_glyph.begin(), i);

    glyph->create();
    sce_world->init_entity(glyph);
  }

  //---------------------------
}

//Glyph camera
void Glyph::create_glyph_camera(utl::entity::Camera* camera){
  //---------------------------

  if(camera->list_glyph.size() != 0) return;
  camera->list_glyph.push_back(new glyph::camera::Target(node_engine));

  for(int i=0; i<camera->list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(camera->list_glyph.begin(), i);

    //Glyph creation
    glyph->create();
    glyph->update_glyph(camera);
    sce_world->init_entity(glyph);
  }

  //---------------------------
}

}
