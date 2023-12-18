#pragma once

#include <Engine/Data/Namespace.h>
#include <Engine/Data/Glyph/Base/Source.h>
#include <Engine/Data/Glyph/Object/Namespace.h>
#include <Utility/Specific/common.h>


namespace eng::data{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(eng::data::Node* eng_data);
  ~Glyph();

public:
  //Init functions
  void create_glyph_world();
  void create_cloud_glyphs(eng::structure::Cloud* cloud);

  //Loop function
  void update_cloud_glyphs(eng::structure::Cloud* cloud);

private:
  glyph::object::AABB* aabb;
  eng::data::Node* eng_data;
  eng::data::Scene* eng_scene;

  vector<glyph::base::Source*> vec_glyph_src;
};

}
