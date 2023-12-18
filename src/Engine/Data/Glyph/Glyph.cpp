#include "Glyph.h"

#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Engine/Engine.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Data/Glyph/World/Namespace.h>


namespace eng::data{

//Constructor / Destructor
Glyph::Glyph(eng::data::Node* eng_data){
  //---------------------------

  Engine* engine = eng_data->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->vk_engine = eng_vulkan->get_vk_engine();
  this->eng_database = eng_data->get_eng_database();
  this->aabb = new glyph::object::AABB();

  this->vec_glyph_src.push_back(new glyph::world::Grid());
  this->vec_glyph_src.push_back(new glyph::world::Axis());

  //---------------------------
}
Glyph::~Glyph(){
  //---------------------------

  for(int i=0; i<vec_glyph_src.size(); i++){
    delete vec_glyph_src[i];
  }

  //---------------------------
}

//Init function
void Glyph::create_glyph_world(){
  //---------------------------

  for(int i=0; i<vec_glyph_src.size(); i++){
    vec_glyph_src[i]->create();
    eng::structure::Glyph* glyph = vec_glyph_src[i]->get_glyph();

    eng::structure::Set* data_set = eng_database->get_data_set();
    eng::structure::Set* set_world = data_set->get_set("World");

    //Insert into engine
    eng_database->assign_ID(glyph);
    glyph->is_suppressible = false;
    vk_engine->insert_object_in_engine(glyph);

    //Insert it into database
    set_world->list_entity.push_back(glyph);
    set_world->selected_entity = glyph;
    set_world->nb_entity++;
  }

  //---------------------------
}
void Glyph::create_cloud_glyphs(eng::structure::Cloud* cloud){
  //---------------------------

  //aabb->create(cloud);
  //eng_scene->insert_object_world(&cloud->aabb);


  //---------------------------
}

//Loop function
void Glyph::update_cloud_glyphs(eng::structure::Cloud* cloud){
  //---------------------------

  aabb->update(cloud);

  //---------------------------
}

}
