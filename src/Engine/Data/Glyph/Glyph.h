#pragma once

#include <Engine/Data/Namespace.h>
#include "Base/Glyph_source.h"
#include <Utility/Specific/common.h>


namespace eng::data{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(eng::data::Node* eng_data);
  ~Glyph();

public:
  //Main functions
  void create_glyph_scene();
  void create_cloud_glyphs(eng::structure::Cloud* cloud);
  Glyph_source* get_glyph_src_byName(string name);

private:
  eng::data::Node* eng_data;
  eng::data::Scene* eng_scene;

  vector<Glyph_source*> vec_glyph_src;
};

}
