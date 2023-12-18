#include "Glyph.h"

#include "../Scene/Scene.h"

#include <Engine/Data/Namespace.h>
#include <Engine/Data/Glyph/World/Namespace.h>


namespace eng::data{

//Constructor / Destructor
Glyph::Glyph(eng::data::Node* eng_data){
  //---------------------------

  this->eng_scene = eng_data->get_eng_scene();
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
    eng_scene->insert_object_world(glyph);
  }

  //---------------------------
}
void Glyph::create_cloud_glyphs(eng::structure::Cloud* cloud){
  //---------------------------

  aabb->create(cloud);
  eng_scene->insert_object_world(&cloud->aabb);


  //---------------------------
}

//Loop function
void Glyph::update_cloud_glyphs(eng::structure::Cloud* cloud){
  //---------------------------

  aabb->update(cloud);

  //---------------------------
}

}
