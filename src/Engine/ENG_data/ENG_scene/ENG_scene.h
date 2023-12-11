#pragma once

#include <Engine/ENG_data/Namespace.h>
#include <Engine/Base/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/UTL_specific/common.h>

class ENG_database;
class VK_engine;
class Attribut;


class ENG_scene
{
public:
  //ConsScenetor / DesScenetor
  ENG_scene(eng::data::ENG_data* eng_data);
  ~ENG_scene();

public:
  //Scene function
  void init_set();
  void init_scene();
  void reset_scene();

  //Insertion / deletion
  void insert_object_glyph(eng::structure::Object* object);
  void insert_object_scene(eng::structure::Object* object);
  void delete_scene_object(eng::structure::Object* object);
  void empty_scene_set();

  //eng::structure::Object
  void selected_object_next();

  //Loop
  void loop();
  void loop_list(list<eng::structure::Set*>* list_data);

  inline eng::structure::Set* get_set_scene(){return set_scene;}
  inline eng::structure::Set* get_set_glyph(){return set_glyph;}
  inline eng::structure::Object* get_selected_object(){return set_scene->selected_obj;}

private:
  eng::data::ENG_data* eng_data;
  ENG_database* eng_database;
  VK_engine* vk_engine;
  Attribut* attributManager;
  eng::camera::Node* eng_camera;

  int ID_obj;
  eng::structure::Set* set_scene;
  eng::structure::Set* set_glyph;
};
