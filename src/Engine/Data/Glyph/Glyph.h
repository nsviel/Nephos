#pragma once

#include <Engine/Data/Namespace.h>
#include "Base/Source.h"
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
  void create_glyph_world();
  void create_cloud_glyphs(eng::structure::Cloud* cloud);
  glyph::base::Source* get_glyph_src_byName(string name);

private:
  eng::data::Node* eng_data;
  eng::data::Scene* eng_scene;

  vector<glyph::base::Source*> vec_glyph_src;
};

}
