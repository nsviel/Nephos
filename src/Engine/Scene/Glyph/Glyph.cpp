#include "Glyph.h"

#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Engine/Engine.h>


namespace eng::scene{

//Constructor / Destructor
Glyph::Glyph(eng::scene::Node* node_scene){
  //---------------------------

  this->engine = node_scene->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->vk_engine = eng_vulkan->get_vk_engine();
  this->sce_database = node_scene->get_scene_database();
  eng::camera::Node* node_camera = engine->get_node_camera();
  this->cam_control = node_camera->get_camera_control();

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

  if(set_world->list_entity.size() != 0) return;
  set_world->insert_entity(new glyph::grid::Grid(engine));
  set_world->insert_entity(new glyph::world::Axis(engine));

  for(int i=0; i<set_world->list_entity.size(); i++){
    entity::Entity* entity = *next(set_world->list_entity.begin(), i);

    if(entity::Glyph* glyph = dynamic_cast<entity::Glyph*>(entity)){
      //Glyph creation
      glyph->create();
      sce_database->assign_ID(glyph);

      //Glyph data
      vector<utl::type::Data*> vec_data = glyph->get_vec_data();
      for(int j=0; j<vec_data.size(); j++){
        sce_database->assign_ID(vec_data[j]);
        vk_engine->insert_data_in_engine(vec_data[j]);
      }
    }
  }

  //---------------------------
}
void Glyph::remove_glyph_world(){
  utl::type::Set* data_set = sce_database->get_data_set();
  utl::type::Set* set_world = data_set->get_set("World");
  //---------------------------

  for(int i=0; i<set_world->list_entity.size(); i++){
    entity::Glyph* glyph = (entity::Glyph*)*next(set_world->list_entity.begin(), i);

    vector<utl::type::Data*> vec_data = glyph->get_vec_data();
    for(int j=0; j<vec_data.size(); j++){
      vk_engine->remove_data_in_engine(vec_data[j]);
    }

    delete glyph;
  }

  //---------------------------
  set_world->list_entity.clear();
}

//Glyph object
void Glyph::create_glyph_object(entity::Object* object){
  //---------------------------

  if(object->list_glyph.size() != 0) return;
  object->list_glyph.push_back(new glyph::object::Axis(engine));
  object->list_glyph.push_back(new glyph::object::AABB(engine));

  for(int i=0; i<object->list_glyph.size(); i++){
    entity::Glyph* glyph = *next(object->list_glyph.begin(), i);

    //Glyph creation
    glyph->create();
    sce_database->assign_ID(glyph);

    //Glyph data
    vector<utl::type::Data*> vec_data = glyph->get_vec_data();
    for(int j=0; j<vec_data.size(); j++){
      sce_database->assign_ID(vec_data[j]);
      vk_engine->insert_data_in_engine(vec_data[j]);
    }
  }

  //---------------------------
}
void Glyph::update_glyph_object(entity::Object* object){
  if(object == nullptr) return;
  //---------------------------

  for(int i=0; i<object->list_glyph.size(); i++){
    entity::Glyph* glyph = *next(object->list_glyph.begin(), i);
    vector<utl::type::Data*> vec_data = glyph->get_vec_data();

    glyph->update_glyph(object);
    for(int j=0; j<vec_data.size(); j++){
      vk_engine->insert_data_in_engine(vec_data[j]);
      cam_control->compute_camera_mvp(vec_data[j]);
    }
  }

  //---------------------------
}
void Glyph::remove_glyph_object(entity::Object* object){
  //---------------------------

  for(int i=0; i<object->list_glyph.size(); i++){
    entity::Glyph* glyph = *next(object->list_glyph.begin(), i);
    vector<utl::type::Data*> vec_data = glyph->get_vec_data();

    for(int j=0; j<vec_data.size(); j++){
      vk_engine->remove_data_in_engine(vec_data[j]);
    }
  }

  //---------------------------
}

//Glyph camera
void Glyph::create_glyph_camera(entity::Camera* camera){
  //---------------------------

  if(camera->list_glyph.size() != 0) return;
  camera->list_glyph.push_back(new glyph::camera::Target(engine));

  for(int i=0; i<camera->list_glyph.size(); i++){
    entity::Glyph* glyph = *next(camera->list_glyph.begin(), i);

    //Glyph creation
    glyph->create();
    glyph->update_glyph(camera);
    sce_database->assign_ID(glyph);

    //Glyph data
    vector<utl::type::Data*> vec_data = glyph->get_vec_data();
    for(int j=0; j<vec_data.size(); j++){
      sce_database->assign_ID(vec_data[j]);
      vk_engine->insert_data_in_engine(vec_data[j]);
    }
  }

  //---------------------------
}

}
