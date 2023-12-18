#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>


namespace glyph::base{

class Source
{
public:
  //Constructor / Destructor
  Source();
  ~Source();

public:
  virtual void create(){}
  virtual void update(){}
  virtual void reset(){}

  inline eng::structure::Glyph* get_glyph(){return glyph;}
  inline string get_name(){return name;}
  inline vec4* get_color(){return &color;}
  inline bool* get_visibility(){return &is_visible;}
  inline void set_visibility(bool value){this->is_visible = value;}

protected:
  eng::structure::Glyph* glyph;

  string name;
  vec4 color;
  bool is_visible;
};

}
