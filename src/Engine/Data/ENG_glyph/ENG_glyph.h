#pragma once

#include <Engine/Data/Namespace.h>
#include "Base/Glyph_source.h"
#include <Utility/UTL_specific/common.h>

class ENG_scene;


class ENG_glyph
{
public:
  //Constructor / Destructor
  ENG_glyph(eng::data::ENG_data* eng_data);
  ~ENG_glyph();

public:
  //Main functions
  void create_glyph_scene();
  Glyph_source* get_glyph_src_byName(string name);

private:
  eng::data::ENG_data* eng_data;
  ENG_scene* eng_scene;

  vector<Glyph_source*> vec_glyph_src;
};
