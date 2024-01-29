#include "Normal.h"

#include <Utility/Function/Math/Math.h>


namespace glyph::object{

//Constructor / destructor
Normal::Normal(eng::Node* engine) : Glyph(engine){
  //---------------------------

  this->name = "normal";
  this->width = 1;
  this->size = 1;
  this->is_visible = false;
  this->color = vec4(0.11f, 0.35f, 0.69f, 1.0f);

  //---------------------------
}
Normal::~Normal(){}
/*
utl::entity::Object* Normal::create(utl::entity::Object* object){
  utl::entity::Object* glyph = new utl::entity::Object(engine);
  //---------------------------

  //Create glyph
  glyph->name = "normal";
  glyph->draw_line_width = width;
  glyph->draw_type_name = "line";
  glyph->unicolor = color;
  glyph->is_visible = is_visible;

  //---------------------------
  return glyph;
}
void Normal::update_normal_cloud(utl::entity::Object* object, utl::entity::Object* glyph){
  glyph->draw_point_size = size;
  //---------------------------

  //Get vector values
  vector<vec3>& xyz_s = cloud->xyz;
  vector<vec3>& Nxyz_s = cloud->Nxyz;
  vector<vec3>& xyz_n = glyph->xyz;
  vector<vec4>& rgb_n = glyph->rgb;

  //Check vector length
  if(xyz_s.size() == 0 || Nxyz_s.size() == 0 || Nxyz_s.size() != xyz_s.size()){
    return;
  }

  //Clear old glyph values
  xyz_n.clear();
  rgb_n.clear();

  //Construct glyph
  float lgt = 0.05 * glyph->draw_point_size;
  for(int i=0; i<xyz_s.size(); i++){
    vec3& xyz = xyz_s[i];
    vec3& nxyz = Nxyz_s[i];

    vec3 vec_n = vec3(xyz.x + nxyz.x * lgt, xyz.y + nxyz.y * lgt, xyz.z + nxyz.z * lgt);

    xyz_n.push_back(xyz);
    xyz_n.push_back(vec_n);

    rgb_n.push_back(glyph->unicolor);
    rgb_n.push_back(glyph->unicolor);
  }

  //---------------------------
}
void Normal::update_normal_cloud(utl::entity::Object* object, vector<vec3>& xyz_s, vector<vec3>& Nxyz_s){
  utl::entity::Object* normal = &cloud->glyphs["normal"];
  normal->draw_point_size = size;
  //---------------------------

  //Get vector values
  vector<vec3>& xyz_n = normal->xyz;
  vector<vec4>& rgb_n = normal->rgb;

  //Check vector length
  if(xyz_s.size() == 0 || Nxyz_s.size() == 0 || Nxyz_s.size() != xyz_s.size()){
    return;
  }

  //Clear old normal values
  xyz_n.clear();
  rgb_n.clear();

  //Construct normal
  float lgt = 0.05 * normal->draw_point_size;
  for(int i=0; i<xyz_s.size(); i++){
    vec3& xyz = xyz_s[i];
    vec3& nxyz = Nxyz_s[i];

    if(math::is_nan(nxyz)) continue;

    vec3 vec_n = vec3(xyz.x + nxyz.x * lgt, xyz.y + nxyz.y * lgt, xyz.z + nxyz.z * lgt);

    xyz_n.push_back(xyz);
    xyz_n.push_back(vec_n);

    rgb_n.push_back(normal->unicolor);
    rgb_n.push_back(normal->unicolor);
  }

  //---------------------------
}*/

}
