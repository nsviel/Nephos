#pragma once

#include <Engine/Operation/Namespace.h>
#include <Engine/Scene/Namespace.h>
#include <Utility/Specific/common.h>

class VK_engine;

namespace eng::scene{
class Glyph;
class Operation;
class Loader;
class Node;
class Database;


class Scene
{
public:
  //Constructor / Destructor
  Scene(eng::scene::Node* node_scene);
  ~Scene();

public:
  //Main function
  void init();
  void loop();
  void reset();

  //Entity function
  utl::type::Entity* import_entity(std::string path);
  void import_entity(utl::type::Entity* entity);
  void init_entity(utl::type::Entity* entity);
  void delete_entity(utl::type::Entity* entity);
  void assign_entity_UID(utl::type::Entity* entity);

  //Set function
  void delete_set(utl::type::Set* set);

  inline utl::type::Set* get_set_scene(){return set_scene;}
  inline utl::type::Set* get_selected_set(){return set_scene->selected_set;}

private:
  VK_engine* vk_engine;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::scene::Loader* sce_loader;
  eng::ope::Attribut* ope_attribut;

  utl::type::Set* set_scene;
};

}
