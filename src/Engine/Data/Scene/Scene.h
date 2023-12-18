#pragma once

#include <Engine/Operation/Namespace.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Base/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>


class VK_engine;


namespace eng::data{
class Node;
class Database;


class Scene
{
public:
  //ConsScenetor / DesScenetor
  Scene(eng::data::Node* eng_data);
  ~Scene();

public:
  //Scene function
  void init_scene();
  void reset_scene();

  //Insertion / deletion
  void insert_object_glyph(eng::structure::Object* object);
  void insert_object_scene(eng::structure::Object* object);
  void update_object(eng::structure::Object* object);
  void delete_scene_object(eng::structure::Object* object);
  void empty_scene_set();

  //eng::structure::Object
  void selected_object_next();
  void provide_new_ID(eng::structure::Object* object);

  //Loop
  void loop();

private:
  eng::data::Node* eng_data;
  eng::data::Database* eng_database;
  VK_engine* vk_engine;
  eng::ope::Attribut* attributManager;
  eng::camera::Node* eng_camera;

  int ID_obj;
};

}
