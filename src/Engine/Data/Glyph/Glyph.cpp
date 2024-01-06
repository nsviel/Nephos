#include "Glyph.h"

#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Engine/Engine.h>


namespace eng::scene{

//Constructor / Destructor
Glyph::Glyph(eng::scene::Node* eng_data){
  //---------------------------

  Engine* engine = eng_data->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->vk_engine = eng_vulkan->get_vk_engine();
  this->eng_database = eng_data->get_eng_database();
  this->eng_camera = engine->get_eng_camera();

  //---------------------------
}
Glyph::~Glyph(){
  //---------------------------

  this->remove_glyph_world();

  //---------------------------
}

//Glyph world
void Glyph::create_glyph_world(){
  eng::data::Set* data_set = eng_database->get_data_set();
  eng::data::Set* set_world = data_set->get_set("World");
  //---------------------------

  this->remove_glyph_world();
  this->list_glyph.push_back(new glyph::grid::Grid());
  this->list_glyph.push_back(new glyph::world::Axis());

  for(int i=0; i<list_glyph.size(); i++){
    eng::data::Glyph* glyph = *next(list_glyph.begin(), i);

    glyph->create();
    eng_database->assign_ID(glyph->get_data());
    vk_engine->insert_object_in_engine(glyph->get_data());
    set_world->insert_entity(glyph->get_data());
  }

  //---------------------------
}
void Glyph::remove_glyph_world(){
  //---------------------------

  for(int i=0; i<list_glyph.size(); i++){
    eng::data::Glyph* glyph = *next(list_glyph.begin(), i);
    vk_engine->remove_object_in_engine(glyph->get_data());
    list_glyph.remove(glyph);
    delete glyph;
  }

  //---------------------------
}

//Glyph object
void Glyph::create_glyph_object(eng::data::Object* object){
  //---------------------------

  object->list_glyph.push_back(new glyph::object::Axis());
  object->list_glyph.push_back(new glyph::object::AABB());
  object->list_glyph.push_back(new glyph::object::Camera());

  for(int i=0; i<object->list_glyph.size(); i++){
    eng::data::Glyph* glyph = *next(object->list_glyph.begin(), i);
    glyph->create();
    eng_database->assign_ID(glyph->get_data());
    vk_engine->insert_object_in_engine(glyph->get_data());
  }

  //---------------------------
}
void Glyph::update_glyph_object(eng::data::Object* object){
  //---------------------------

  for(int i=0; i<object->list_glyph.size(); i++){
    eng::data::Glyph* glyph = *next(object->list_glyph.begin(), i);
    glyph->update(object);
    vk_engine->insert_object_in_engine(glyph->get_data());
    eng_camera->compute_cam_mvp(glyph->get_data());
  }

  //---------------------------
}
void Glyph::remove_glyph_object(eng::data::Object* object){
  //---------------------------

  for(int i=0; i<object->list_glyph.size(); i++){
    eng::data::Glyph* glyph = *next(object->list_glyph.begin(), i);
    vk_engine->remove_object_in_engine(glyph->get_data());
  }

  //---------------------------
}

}
