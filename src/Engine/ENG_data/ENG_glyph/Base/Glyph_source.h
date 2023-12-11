#pragma once

#include <Utility/UTL_base/Struct_glyph.h>
#include <Utility/UTL_specific/common.h>


class Glyph_source
{
public:
  //Constructor / Destructor
  Glyph_source();
  ~Glyph_source();

public:
  virtual void create_glyph(){}
  virtual void update_glyph(){}
  virtual void reset_glyph(){}
  virtual void reset(){}

  inline data::Glyph* get_glyph(){return glyph;}
  inline string get_name(){return name;}
  inline vec4* get_color(){return &color;}
  inline bool* get_visibility(){return &is_visible;}
  inline void set_visibility(bool value){this->is_visible = value;}

protected:
  data::Glyph* glyph;

  string name;
  vec4 color;
  bool is_visible;
};
