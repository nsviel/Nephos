#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>


namespace eng::data{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(){
    //---------------------------

    this->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->is_visible = true;

    //---------------------------
  }
  ~Glyph(){
    //---------------------------

    delete glyph;

    //---------------------------
  }

public:
  virtual eng::data::Object* create(){return glyph;}
  virtual void update(){}
  virtual void reset(){}

  inline eng::data::Object* get_glyph(){return glyph;}
  inline string get_name(){return name;}
  inline vec4* get_color(){return &color;}
  inline bool* get_visibility(){return &is_visible;}
  inline void set_visibility(bool value){this->is_visible = value;}

protected:
  eng::data::Object* glyph;

  string name;
  vec4 color;
  bool is_visible;
};

}
