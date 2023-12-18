#pragma once

#include "../Base/Glyph_source.h"


namespace glyph::object{

class Normal : public Glyph_source
{
public:
  //Constructor / Destructor
  Normal();
  ~Normal();

public:
  eng::structure::Glyph* create(eng::structure::Object* object);
  void update_normal_cloud(eng::structure::Object* object, eng::structure::Glyph* glyph);
  void update_normal_cloud(eng::structure::Object* object, vector<vec3>& xyz_s, vector<vec3>& Nxyz_s);

  inline bool* get_visibility(){return &visibility;}
  inline int* get_size(){return &size;}

private:
  bool visibility;
  vec4 color;
  int size;
  int width;
};

}
