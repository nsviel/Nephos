#pragma once

#include <Utility/Specific/common.h>

namespace vk::main{class Engine;}
namespace eng::scene{class Node;}
namespace eng::scene{class Glyph;}
namespace eng::scene{class Operation;}
namespace eng::scene{class Loader;}
namespace eng::scene{class Database;}
namespace eng::ope{class Attribut;}


namespace eng::scene{

class Scene
{
public:
  //Constructor / Destructor
  Scene(eng::scene::Node* sce_node);
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
  void delete_scene_entity(utl::type::Entity* entity);
  void assign_entity_UID(utl::type::Entity* entity);

  //Set function
  void delete_set(utl::type::Set* set);

  inline utl::type::Set* get_set_scene(){return set_scene;}
  inline utl::type::Set* get_selected_set(){return set_scene->selected_set;}

private:
  vk::main::Engine* vk_engine;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::scene::Loader* sce_loader;
  eng::ope::Attribut* ope_attribut;

  utl::type::Set* set_scene;
};

}
