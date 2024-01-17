#pragma once

#include <Utility/Base/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;

namespace entity{
class Object;


class Glyph : public entity::Entity
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
  virtual void update_glyph(entity::Entity* entity){}
  virtual void reset(){}

  inline vector<utl::type::Data*>& get_vec_data(){return vec_data;}
  inline vec4* get_color(){return &color;}

protected:
  Engine* engine;
  vector<utl::type::Data*> vec_data;

  vec4 color;
};

}
