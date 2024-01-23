#pragma once

#include <Engine/Data/Node.h>
#include <Engine/Data/src/Database/Database.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>

#include <Engine/Data/src/Glyph/World/Namespace.h>
#include <Engine/Data/src/Glyph/Object/Namespace.h>
#include <Engine/Data/src/Glyph/Grid/Namespace.h>
#include <Engine/Data/src/Glyph/Camera/Namespace.h>

class VK_engine;


namespace eng::scene{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(eng::scene::Node* node_scene);
  ~Glyph();

public:
  //Glyph world
  void create_glyph_world();
  void remove_glyph_world();

  //Glyph object
  void create_glyph_object(utl::entity::Object* object);
  void remove_glyph_object(utl::entity::Object* object);

  //Glyph camera
  void create_glyph_camera(utl::entity::Camera* camera);

private:
  Engine* engine;
  VK_engine* vk_engine;
  eng::scene::Node* node_scene;
  eng::scene::Database* sce_database;
  eng::scene::World* sce_world;
  eng::cam::Control* cam_control;
};

}
