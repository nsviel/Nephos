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

  this->glyph_aabb = new glyph::object::AABB();
  this->glyph_axis = new glyph::object::Axis();

  this->vec_glyph.push_back(new glyph::world::Grid());
  this->vec_glyph.push_back(new glyph::world::Axis());

  //---------------------------
}
Glyph::~Glyph(){
  //---------------------------

  for(int i=0; i<vec_glyph.size(); i++){
    delete vec_glyph[i];
  }

  //---------------------------
}

//Init function
void Glyph::create_glyph_world(){
  //---------------------------

  for(int i=0; i<vec_glyph.size(); i++){
    eng::data::Set* data_set = eng_database->get_data_set();
    eng::data::Set* set_world = data_set->get_set("World");
    eng::base::Glyph* base = vec_glyph[i];
    eng::data::Object* glyph = base->create();

    //Insert into engine
    eng_database->assign_ID(glyph);
    glyph->is_suppressible = false;
    vk_engine->insert_object_in_engine(glyph);
    set_world->insert_entity(glyph);
  }

  //---------------------------
}

//Cloud function
void Glyph::create_cloud_glyphs(eng::data::Object* object){
  //---------------------------

  //AABB
  glyph_aabb->create(object);
  eng_database->assign_ID(object->aabb);
  vk_engine->insert_object_in_engine(object->aabb);

  //Axis
  glyph_axis->create(object);
  eng_database->assign_ID(object->axis);
  vk_engine->insert_object_in_engine(object->axis);

  //Camera
  glyph_cam->create(object);
  eng_database->assign_ID(object->camera);
  vk_engine->insert_object_in_engine(object->camera);

  //---------------------------
}
void Glyph::update_cloud_glyphs(eng::data::Object* object){
  //---------------------------
/*
  //AABB
  glyph_aabb->update(object);
  vk_engine->insert_object_in_engine(object->aabb);
  eng_camera->compute_cam_mvp(object->aabb);

  //AABB
  glyph_axis->update(object);
  vk_engine->insert_object_in_engine(object->axis);
  eng_camera->compute_cam_mvp(object->axis);

  //AABB
  glyph_cam->update(object);
  vk_engine->insert_object_in_engine(object->camera);
  eng_camera->compute_cam_mvp(object->camera);
*/
  //---------------------------
}
void Glyph::remove_cloud_glyphs(eng::data::Object* object){
  //---------------------------

  vk_engine->remove_object_in_engine(object->aabb);
  vk_engine->remove_object_in_engine(object->axis);
  vk_engine->remove_object_in_engine(object->camera);

  //---------------------------
}

}
