#pragma once

#include <Engine/Data/Node.h>
#include <Engine/Data/Scene/Database.h>
#include <Engine/Data/Glyph/World/Namespace.h>
#include <Engine/Base/Base_glyph.h>
#include <Engine/Data/Glyph/Object/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>

class VK_engine;


namespace eng::scene{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(eng::scene::Node* eng_data);
  ~Glyph();

public:
  //Init functions
  void create_glyph_world();

  //Subfunction
  void create_cloud_glyphs(eng::data::Object* object);
  void update_cloud_glyphs(eng::data::Object* object);
  void remove_cloud_glyphs(eng::data::Object* object);

private:
  VK_engine* vk_engine;
  glyph::object::AABB* glyph_aabb;
  glyph::object::Axis* glyph_axis;
  glyph::object::Camera* glyph_cam;
  eng::scene::Node* eng_data;
  eng::scene::Database* eng_database;
  eng::camera::Node* eng_camera;

  vector<eng::base::Glyph*> vec_glyph;
};

}
