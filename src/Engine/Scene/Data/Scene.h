#pragma once

#include <Engine/Scene/Glyph/Glyph.h>
#include <Engine/Operation/Namespace.h>
#include <Engine/Scene/Data/Database.h>
#include <Engine/Scene/Data/Operation.h>
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
  eng::base::Entity* get_selected_entity();

  //Entity
  eng::base::Entity* import_entity(std::string path);
  void insert_entity_scene(eng::base::Entity* entity);
  void delete_entity(eng::base::Entity* object);
  void delete_entity_all();

  //Object
  void insert_object_scene(eng::base::Object* object);
  void insert_object(eng::base::Object* object);
  void update_object(eng::base::Object* object);
  void remove_object(eng::base::Object* object);

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
