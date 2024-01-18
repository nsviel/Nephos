#pragma once

#include <Engine/Scene/Node.h>
#include <Engine/Scene/Database/Database.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>

#include <Engine/Scene/Glyph/World/Namespace.h>
#include <Engine/Scene/Glyph/Object/Namespace.h>
#include <Engine/Scene/Glyph/Grid/Namespace.h>
#include <Engine/Scene/Glyph/Camera/Namespace.h>

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
  void create_glyph_object(entity::Object* object);
  void update_glyph_object(entity::Object* object);
  void remove_glyph_object(entity::Object* object);

  //Glyph camera
  void create_glyph_camera(entity::Camera* camera);

private:
  Engine* engine;
  VK_engine* vk_engine;
  eng::scene::Node* node_scene;
  eng::scene::Database* sce_database;
  eng::camera::Control* cam_control;
};

}
