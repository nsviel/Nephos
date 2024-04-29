#pragma once

#include <Utility/Specific/Common.h>

namespace eng::scene{class Node;}
namespace eng::scene{class Database;}
namespace eng::scene{class Entity;}
namespace eng::scene{class Set;}
namespace eng::scene{class Loader;}
namespace cam{class Control;}
namespace cam{class Entity;}


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

  //Glyph init
  void create_glyph_world();
  void create_glyph_object(utl::entity::Object* object);
  void create_glyph_camera(cam::Entity* camera);

  //Glyph creation
  void create_glyph(utl::type::Set* set, utl::entity::Glyph* glyph);
  void create_glyph(utl::type::Entity* entity, utl::entity::Glyph* glyph);

private:
  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  eng::scene::Database* sce_database;
  eng::scene::Set* sce_set;
  eng::scene::Entity* sce_entity;
  eng::scene::Loader* sce_loader;
  cam::Control* cam_control;
};

}
