#pragma once

#include <Engine/Scene/Glyph/Glyph.h>
#include <Engine/Operation/Namespace.h>
#include <Engine/Scene/Data/Database.h>
#include <Engine/Scene/Glyph/Glyph.h>
#include <Engine/Scene/Node.h>

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
  utl::type::Entity* import_entity(std::string path);
  void delete_entity(utl::type::Entity* entity);
  void assign_entity_UID(utl::type::Entity* entity);
  void update_entity(utl::type::Entity* entity);

  //Object
  void insert_object(entity::Object* object);
  void remove_object(entity::Object* object);

  inline utl::type::Set* get_set_scene(){return set_scene;}

private:
  VK_engine* vk_engine;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::scene::Loader* sce_loader;
  eng::ope::Attribut* ope_attribut;

  utl::type::Set* set_scene;
};

}
