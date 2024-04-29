#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace sce{class Node;}
namespace dat{class Database;}
namespace dat{class Entity;}
namespace dat{class Set;}
namespace ldr{class Loader;}
namespace cam{class Control;}
namespace cam{class Entity;}


namespace dat{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(eng::Node* node_engine);
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
  sce::Node* node_scene;
  dat::Database* dat_database;
  dat::Set* dat_set;
  dat::Entity* dat_entity;
  ldr::Loader* ldr_loader;
  cam::Control* cam_control;
};

}
