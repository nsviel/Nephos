#pragma once

#include <Engine/Scene/Glyph/Glyph.h>
#include <Engine/Operation/Namespace.h>
#include <Engine/Scene/Data/Database.h>
#include <Engine/Scene/Data/Operation.h>
#include <Engine/Scene/Glyph/Glyph.h>
#include <Engine/Scene/Node.h>
#include <Engine/Base/Namespace.h>
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
  eng::data::Entity* get_selected_entity();

  //Entity
  eng::data::Entity* import_entity(std::string path);
  void insert_entity_scene(eng::data::Entity* entity);
  void delete_entity(eng::data::Entity* object);
  void delete_entity_all();

  //Object
  void insert_object_scene(eng::data::Object* object);
  void insert_object(eng::data::Object* object);
  void update_object(eng::data::Object* object);
  void remove_object(eng::data::Object* object);

private:
  VK_engine* vk_engine;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::scene::Operation* sce_operation;
  eng::scene::Loader* sce_loader;
  eng::ope::Attribut* ope_attribut;

  int ID_obj;
};

}
