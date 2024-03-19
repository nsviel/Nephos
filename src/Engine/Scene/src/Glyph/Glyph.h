#pragma once

#include <Utility/Specific/common.h>

namespace vk::main{class Graphical;}
namespace eng::scene{class Node;}
namespace eng::scene{class Database;}
namespace eng::scene{class Entity;}
namespace eng::scene{class Set;}
namespace eng::cam{class Control;}


namespace eng::scene{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(eng::scene::Node* node_scene);
  ~Glyph();

public:
  //Main function
  void init();

  //Glyph function
  void create_glyph_world();
  void create_glyph_scene();
  void create_glyph_object(utl::entity::Object* object);
  void create_glyph_camera(utl::entity::Camera* camera);

  //Subfunction
  void create_glyph(utl::type::Set* set, utl::entity::Glyph* glyph);
  void create_glyph(utl::type::Entity* entity, utl::entity::Glyph* glyph);

private:
  eng::Node* node_engine;
  vk::main::Graphical* vk_graphical;
  eng::scene::Node* node_scene;
  eng::scene::Database* sce_database;
  eng::scene::Set* sce_set;
  eng::scene::Entity* sce_entity;
  eng::cam::Control* cam_control;
};

}
