#pragma once

#include <Utility/Base/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;

namespace eng::base{


class Glyph : public eng::base::Entity
{
public:
  //Constructor / Destructor
  Glyph(Engine* engine);
  ~Glyph();

  //Main function
  void update_entity();
  void visibility_entity(bool value);

  virtual void create(){}
  virtual void update_glyph(){}
  virtual void update_glyph(eng::base::Entity* entity){}
  virtual void reset(){}

  inline vector<eng::base::Object*>& get_vec_object(){return vec_object;}
  inline vec4* get_color(){return &color;}
  inline bool* get_visibility(){return &is_visible;}

protected:
  Engine* engine;
  vector<eng::base::Object*> vec_object;

  vec4 color;
  bool is_visible;
};

}
