#pragma once

#include <Engine/Base/Base_glyph.h>


namespace glyph::object{

class Normal : public eng::data::Glyph
{
public:
  //Constructor / Destructor
  Normal();
  ~Normal();

public:
  eng::data::Object* create(eng::data::Object* object);
  void update_normal_cloud(eng::data::Object* object, eng::data::Object* glyph);
  void update_normal_cloud(eng::data::Object* object, vector<vec3>& xyz_s, vector<vec3>& Nxyz_s);

  inline bool* get_visibility(){return &visibility;}
  inline int* get_size(){return &size;}

private:
  bool visibility;
  vec4 color;
  int size;
  int width;
};

}
