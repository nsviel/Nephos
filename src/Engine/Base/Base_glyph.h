#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>


namespace eng::data{

class Glyph : public eng::data::Entity
{
public:
  //Constructor / Destructor
  Glyph(){
    //---------------------------

    this->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->is_visible = true;
    this->type = "Glyph";

    //---------------------------
  }
  ~Glyph(){}

public:
  virtual void create(){}
  virtual void update(){}
  virtual void update(eng::data::Object* object){}
  virtual void reset(){}

  inline vector<eng::data::Object*> get_vec_object(){return vec_object;}
  inline vec4* get_color(){return &color;}
  inline bool* get_visibility(){return &is_visible;}
  inline void set_visibility(bool value){this->is_visible = value;}

protected:
  vector<eng::data::Object*> vec_object;

  vec4 color;
  bool is_visible;
};

}
