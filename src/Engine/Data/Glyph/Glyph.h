#pragma once

#include <Engine/Data/Node.h>
#include <Engine/Data/Scene/Database.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>

#include <Engine/Data/Glyph/World/Namespace.h>
#include <Engine/Data/Glyph/Object/Namespace.h>
#include <Engine/Data/Glyph/Grid/Namespace.h>

class VK_engine;


namespace eng::scene{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(eng::scene::Node* eng_data);
  ~Glyph();

public:
  //Glyph world
  void create_glyph_world();
  void remove_glyph_world();

  //Glyph object
  void create_glyph_object(eng::data::Object* object);
  void update_glyph_object(eng::data::Object* object);
  void remove_glyph_object(eng::data::Object* object);

private:
  VK_engine* vk_engine;
  glyph::object::Camera* glyph_cam;
  eng::scene::Node* eng_data;
  eng::scene::Database* sce_database;
  eng::camera::Node* eng_camera;

  list<eng::data::Glyph*> list_glyph;
};

}
