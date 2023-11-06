#ifndef ENG_SCENE_H
#define ENG_SCENE_H

#include <ELE_specific/common.h>

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
  void insert_glyph_object(Object* object);
  void insert_scene_object(Object* object);
  void delete_scene_object(Object* object);
  void empty_scene_set();

  //Object
  void selected_object_next();

  //Loop
  void loop();
  void loop_list(list<Set*>* list_data);

  inline Set* get_set_scene(){return set_scene;}
  inline Set* get_set_glyph(){return set_glyph;}
  inline Object* get_selected_object(){return set_scene->selected_obj;}

private:
  ENG_data* eng_data;
  ENG_database* eng_database;
  VK_engine* vk_engine;
  Attribut* attributManager;
  ENG_camera* eng_camera;

  int ID_obj;
  Set* set_scene;
  Set* set_glyph;
};


#endif
