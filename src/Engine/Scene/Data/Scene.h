#pragma once

#include <Engine/Scene/Glyph/Glyph.h>
#include <Engine/Operation/Namespace.h>
#include <Engine/Scene/Data/Database.h>
#include <Engine/Scene/Glyph/Glyph.h>
#include <Engine/Scene/Node.h>
#include <Utility/Base/Namespace.h>
#include <Utility/Specific/common.h>

class VK_engine;

namespace eng::scene{
class Glyph;
class Operation;


class Scene
{
public:
  //ConsScenetor / DesScenetor
  Scene(eng::scene::Node* node_scene);
  ~Scene();

public:
  //Scene function
  void init();
  void loop();
  void reset();

  //Entity
  entity::Entity* get_selected_entity();
  entity::Entity* import_entity(std::string path);
  void insert_set_scene(utl::type::Set* set);
  void insert_entity_scene(entity::Entity* entity);
  void delete_entity(entity::Entity* entity);
  void delete_entity_all();

  //Object
  void insert_object(entity::Object* object);
  void remove_object(entity::Object* object);

  //Data
  void update_data(utl::type::Data* data);

private:
  VK_engine* vk_engine;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::scene::Loader* sce_loader;
  eng::ope::Attribut* ope_attribut;

  int ID_obj;
};

}
