#pragma once

#include <Utility/Specific/common.h>

namespace vk::main{class Graphical;}
namespace eng::scene{class Node;}
namespace eng::scene{class Glyph;}
namespace eng::scene{class Operation;}
namespace eng::scene{class Database;}
namespace eng::ope{class Attribut;}


namespace eng::scene{

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
  void import_entity(utl::type::Entity* entity);
  void init_entity(utl::type::Entity* entity);
  void delete_scene_entity(utl::type::Entity* entity);
  void assign_entity_UID(utl::type::Entity* entity);

  //Set function
  void delete_set(utl::type::Set* set);

  inline utl::type::Set* get_set_scene(){return set_scene;}
  inline utl::type::Entity* get_selected_entity(){return set_scene->selected_entity;}

private:
  vk::main::Graphical* vk_graphical;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::ope::Attribut* ope_attribut;

  utl::type::Set* set_scene;
};

}
