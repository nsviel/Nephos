#pragma once

#include <Utility/Base/Entity/Glyph.h>


namespace glyph::object{

class Normal : public entity::Glyph
{
public:
  //Constructor / Destructor
  Normal(Engine* engine);
  ~Normal();

public:
  entity::Object* create(entity::Object* object);
  void update_normal_cloud(entity::Object* object, entity::Object* glyph);
  void update_normal_cloud(entity::Object* object, vector<vec3>& xyz_s, vector<vec3>& Nxyz_s);

  inline bool* get_visibility(){return &visibility;}
  inline int* get_size(){return &size;}

private:
  bool visibility;
  vec4 color;
  int size;
  int width;
};

}
