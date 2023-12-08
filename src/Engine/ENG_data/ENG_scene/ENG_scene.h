#ifndef ENG_SCENE_H
#define ENG_SCENE_H

#include <UTL_specific/common.h>

class ENG_data;
class ENG_database;
class VK_engine;
class Attribut;
class ENG_camera;


class ENG_scene
{
public:
  //ConsScenetor / DesScenetor
  ENG_scene(ENG_data* eng_data);
  ~ENG_scene();

public:
  //Scene function
  void init_set();
  void init_scene();
  void reset_scene();

  //Insertion / deletion
  void insert_object_glyph(data::Object* object);
  void insert_object_scene(data::Object* object);
  void delete_scene_object(data::Object* object);
  void empty_scene_set();

  //data::Object
  void selected_object_next();

  //Loop
  void loop();
  void loop_list(list<data::Set*>* list_data);

  inline data::Set* get_set_scene(){return set_scene;}
  inline data::Set* get_set_glyph(){return set_glyph;}
  inline data::Object* get_selected_object(){return set_scene->selected_obj;}

private:
  ENG_data* eng_data;
  ENG_database* eng_database;
  VK_engine* vk_engine;
  Attribut* attributManager;
  ENG_camera* eng_camera;

  int ID_obj;
  data::Set* set_scene;
  data::Set* set_glyph;
};


#endif
