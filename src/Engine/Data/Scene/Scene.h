#pragma once

#include <Engine/Data/Glyph/Glyph.h>
#include <Engine/Operation/Namespace.h>
#include <Engine/Data/Scene/Database.h>
#include <Engine/Data/Glyph/Glyph.h>
#include <Engine/Data/Node.h>
#include <Engine/Base/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>

class VK_engine;


namespace eng::scene{
class Glyph;

class Scene
{
public:
  //ConsScenetor / DesScenetor
  Scene(eng::scene::Node* eng_data);
  ~Scene();

public:
  //Scene function
  void init();
  void loop();
  void reset();

  //Insertion / deletion
  void insert_object_scene(eng::structure::Object* object);
  void update_object(eng::structure::Object* object);
  void delete_object_scene(eng::structure::Entity* object);
  void delete_object_scene_all();

private:
  VK_engine* vk_engine;
  eng::scene::Node* eng_data;
  eng::scene::Database* eng_database;
  eng::scene::Glyph* eng_glyph;
  eng::ope::Attribut* attributManager;
  eng::camera::Node* eng_camera;

  int ID_obj;
};

}
