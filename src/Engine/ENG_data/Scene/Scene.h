#ifndef SCENE_GG_H
#define SCENE_GG_H

#include <ELE_specific/common.h>

class Data;
class Database;
class GPU_data;
class Attribut;


class Scene
{
public:
  //ConsScenetor / DesScenetor
  Scene(Data* data);
  ~Scene();

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

  inline Set* get_set_scene(){return set_scene;}
  inline Set* get_set_glyph(){return set_glyph;}
  inline Object* get_selected_object(){return set_scene->selected_obj;}

private:
  Data* data;
  Database* dataManager;
  GPU_data* gpu_data;
  Attribut* attributManager;

  int ID_obj;
  Set* set_scene;
  Set* set_glyph;
};


#endif
