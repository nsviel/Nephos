#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace sce{class Node;}
namespace sce{class Database;}
namespace sce{class Entity;}
namespace sce{class Set;}
namespace sce{class Loader;}
namespace cam{class Control;}
namespace cam{class Entity;}


namespace sce{

class Manager
{
public:
  //Constructor / Destructor
  Manager(sce::Node* node_scene);
  ~Manager();

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
  sce::Node* node_scene;
  sce::Database* sce_database;
  sce::Set* sce_set;
  sce::Entity* sce_entity;
  sce::Loader* sce_loader;
  cam::Control* cam_control;
};

}
