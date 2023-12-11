#include "ENG_glyph.h"

#include "Base/Glyph_source.h"
#include "Scene/Grid.h"
#include "Scene/Axis_world.h"

#include "../ENG_data.h"
#include "../ENG_scene/ENG_scene.h"


//Constructor / Destructor
ENG_glyph::ENG_glyph(ENG_data* eng_data){
  //---------------------------

  this->eng_scene = eng_data->get_eng_scene();

  this->vec_glyph_src.push_back(new Grid());
  this->vec_glyph_src.push_back(new Axis_world());

  //---------------------------
}
ENG_glyph::~ENG_glyph(){
  //---------------------------

  for(int i=0; i<vec_glyph_src.size(); i++){
    delete vec_glyph_src[i];
  }

  //---------------------------
}

//Creation function
void ENG_glyph::create_glyph_scene(){
  //---------------------------

  for(int i=0; i<vec_glyph_src.size(); i++){
    vec_glyph_src[i]->create_glyph();
    eng::structure::Glyph* glyph = vec_glyph_src[i]->get_glyph();
    eng_scene->insert_object_glyph(glyph);
  }

  //---------------------------
}
Glyph_source* ENG_glyph::get_glyph_src_byName(string name){
  //---------------------------

  for(int i=0; i<vec_glyph_src.size(); i++){
    if(name == vec_glyph_src[i]->get_name()){
      return vec_glyph_src[i];
    }
  }

  //---------------------------
  return nullptr;
}


/*
//Main functions
void ENG_glyph::draw_glyph(eng::structure::Glyph* glyph){
  //---------------------------

  if(glyph->is_visible){
    gpuManager->draw_object(glyph);
  }

  //---------------------------
}
void ENG_glyph::insert_into_gpu(eng::structure::Glyph* glyph){
  //---------------------------

  gpuManager->gen_vao(glyph);
  gpuManager->gen_buffer_location(glyph);
  gpuManager->gen_buffer_color(glyph);
  gpuManager->convert_draw_type_byName(glyph);

  //---------------------------
}

//eng::structure::Glyph creation / supression
void ENG_glyph::create_glyph_scene(eng::structure::Glyph* glyph){
  eng::structure::Set* col_glyph = eng_data->get_collection_byName("glyph", "glyph_scene");
  //---------------------------

  this->insert_into_gpu(glyph);
  col_glyph->obj_add_new(glyph);

  //---------------------------
}
void ENG_glyph::create_glyph_object(eng::structure::Object* object, eng::structure::Glyph* glyph){
  eng::structure::Set* col_glyph = eng_data->get_collection_byName("glyph", "glyph_object");
  //---------------------------

  glyph->linked_object = cloud;
  this->insert_into_gpu(glyph);
  col_glyph->obj_add_new(glyph);

  //---------------------------
}
void ENG_glyph::remove_temporary_glyph(){
  eng::structure::Set* col_glyph = eng_data->get_collection_byName("glyph", "glyph_scene");
  //---------------------------

  //Remove non permanent glyphs
  for(int i=0; i<col_glyph->list_obj.size(); i++){
    eng::structure::Glyph* glyph = (eng::structure::Glyph*)*next(col_glyph->list_obj.begin(),i);

    if(glyph->is_permanent == false){
      this->remove_glyph_scene(glyph->ID);
      i = 0;
    }
  }

  //---------------------------
}
void ENG_glyph::remove_glyph_scene(int ID){
  eng::structure::Set* col_glyph = eng_data->get_collection_byName("glyph", "glyph_scene");
  //---------------------------

  for(int i=0;i<col_glyph->list_obj.size();i++){
    eng::structure::Glyph* glyph = (eng::structure::Glyph*)*next(col_glyph->list_obj.begin(),i);

    if(glyph->ID == ID){
      delete glyph;
      list<Object_*>::iterator it = next(col_glyph->list_obj.begin(), i);
      col_glyph->list_obj.erase(it);
    }
  }

  //---------------------------
}
eng::structure::Glyph* ENG_glyph::create_glyph(vector<vec3>& XYZ, vector<vec4>& RGB, string mode, bool perma){
  eng::structure::Set* col_glyph = eng_data->get_collection_byName("glyph", "glyph_scene");
  eng::structure::Glyph* glyph = new eng::structure::Glyph();
  unsigned int VAO;
  uint colorVBO, locationVBO;
  //---------------------------

  glyph->xyz = XYZ;
  glyph->rgb = RGB;
  glyph->name = "...";
  glyph->draw_type_name = mode;
  glyph->draw_line_width = 1;
  glyph->is_permanent = perma;

  this->insert_into_gpu(glyph);
  col_glyph->list_obj.push_back(glyph);

  //---------------------------
  return glyph;
}

//eng::structure::Glyph update
void ENG_glyph::update_glyph_buffer(eng::structure::Glyph* glyph){
  //---------------------------

  gpuManager->update_buffer_location(glyph);
  gpuManager->update_buffer_color(glyph);

  //---------------------------
}
void ENG_glyph::update_glyph_location(eng::structure::Glyph* glyph){
  //---------------------------

  gpuManager->update_buffer_location(glyph);

  //---------------------------
}
void ENG_glyph::update_glyph_color(eng::structure::Glyph* glyph){
  //---------------------------

  gpuManager->update_buffer_color(glyph);

  //---------------------------
}
void ENG_glyph::update_glyph_color(eng::structure::Glyph* glyph, vec4 RGB_new){
  vector<vec4>& RGB = glyph->rgb;
  int size = RGB.size();
  //---------------------------

  //Change internal glyph color
  RGB.clear();
  for(int i=0; i<size; i++){
    RGB.push_back(RGB_new);
  }
  glyph->unicolor = RGB_new;

  //Reactualise vertex color data
  gpuManager->update_buffer_color(glyph);

  //---------------------------
}
void ENG_glyph::update_glyph_MinMax(eng::structure::Glyph* glyph){
  vector<vec3>& XYZ = glyph->xyz;
  vec3 min = XYZ[0];
  vec3 max = XYZ[0];
  vec3 centroid = vec3(0, 0, 0);
  //---------------------------

  for(int i=0; i<XYZ.size(); i++){
    for(int j=0; j<3; j++){
      if ( XYZ[i][j] <= min[j] ) min[j] = XYZ[i][j];
      if ( XYZ[i][j] >= max[j] ) max[j] = XYZ[i][j];
      centroid[j] += XYZ[i][j];
    }
  }

  for(int j=0;j<3;j++){
    centroid[j] /= XYZ.size();
  }

  //---------------------------
  glyph->min = min;
  glyph->max = max;
  glyph->COM = centroid;
}
*/
