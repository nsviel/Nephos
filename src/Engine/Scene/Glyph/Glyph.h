#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace scene{class Node;}
namespace scene{class Database;}
namespace scene{class Entity;}
namespace scene{class Set;}
namespace scene{class Loader;}
namespace cam{class Control;}
namespace cam{class Entity;}


namespace scene{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(scene::Node* node_scene);
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
  scene::Node* node_scene;
  scene::Database* sce_database;
  scene::Set* sce_set;
  scene::Entity* sce_entity;
  scene::Loader* sce_loader;
  cam::Control* cam_control;
};

}
