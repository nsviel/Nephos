#pragma once

#include <Utility/Specific/common.h>

namespace vk::main{class Graphical;}
namespace eng::scene{class Node;}
namespace eng::scene{class Glyph;}
namespace eng::scene{class Operation;}
namespace eng::scene{class Database;}


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
  void init_entity(utl::type::Entity* entity);
  void assign_entity_UID(utl::type::Entity* entity);

  //Set function
  void delete_subset(utl::type::Set* set);
  utl::type::Set* get_or_create_subset(string name);

  inline utl::type::Set* get_set_scene(){return set_scene;}
  inline utl::type::Entity* get_selected_entity(){return set_scene->selected_entity;}
  inline void set_selected_entity(utl::type::Entity* entity){set_scene->selected_entity = entity;}

private:
  vk::main::Graphical* vk_graphical;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;

  utl::type::Set* set_scene;
};

}