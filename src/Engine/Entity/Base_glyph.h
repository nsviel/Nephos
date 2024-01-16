#pragma once

#include <Engine/Entity/Namespace.h>
#include <Utility/Specific/common.h>


namespace eng::data{

class Glyph : public eng::data::Entity
{
public:
  //Constructor / Destructor
  Glyph();
  ~Glyph();

public:
  virtual void create(){}
  virtual void update_glyph(){}
  virtual void update_glyph(eng::data::Entity* entity){}
  virtual void reset(){}

  inline vector<eng::data::Object*> get_vec_object(){return vec_object;}
  inline vec4* get_color(){return &color;}
  inline bool* get_visibility(){return &is_visible;}

protected:
  vector<eng::data::Object*> vec_object;

  vec4 color;
  bool is_visible;
};

}
