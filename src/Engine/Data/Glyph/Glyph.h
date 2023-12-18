#pragma once

#include <Engine/Data/Node.h>
#include <Engine/Data/Scene/Database.h>
#include <Engine/Data/Glyph/World/Namespace.h>
#include <Engine/Data/Glyph/Base/Source.h>
#include <Engine/Data/Glyph/Object/Namespace.h>
#include <Utility/Specific/common.h>

class VK_engine;


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
  VK_engine* vk_engine;
  glyph::object::AABB* glyph_aabb;
  glyph::object::Axis* glyph_axis;
  eng::data::Node* eng_data;
  eng::data::Database* eng_database;

  vector<glyph::base::Source*> vec_glyph_src;
};

}
