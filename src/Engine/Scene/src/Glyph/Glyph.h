#pragma once

#include <Utility/Specific/common.h>

namespace vk::main{class Graphical;}
namespace eng::scene{class Node;}
namespace eng::scene{class Database;}
namespace eng::scene{class World;}
namespace eng::cam{class Control;}


namespace eng::scene{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(eng::scene::Node* node_scene);
  ~Glyph();

public:
  //Glyph world
  void create_glyph_world();
  void remove_glyph_world();

  //Glyph object
  void create_glyph_object(utl::entity::Object* object);

  //Glyph camera
  void create_glyph_camera(utl::entity::Camera* camera);

private:
  eng::Node* node_engine;
  vk::main::Graphical* vk_graphical;
  eng::scene::Node* node_scene;
  eng::scene::Database* sce_database;
  eng::scene::World* sce_world;
  eng::cam::Control* cam_control;
};

}
