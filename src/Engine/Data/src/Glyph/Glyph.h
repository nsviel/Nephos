#pragma once

#include <Utility/Specific/common.h>

class VK_engine;
namespace eng::scene{class Node;}
namespace eng::scene{class Database;}
namespace eng::scene{class World;}
namespace eng::cam{class Control;}


namespace eng::scene{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(eng::scene::Node* sce_node);
  ~Glyph();

public:
  //Glyph world
  void create_glyph_world();
  void remove_glyph_world();

  //Glyph object
  void create_glyph_object(utl::entity::Object* object);
  void remove_glyph_object(utl::entity::Object* object);

  //Glyph camera
  void create_glyph_camera(utl::entity::Camera* camera);

private:
  Engine* engine;
  VK_engine* vk_engine;
  eng::scene::Node* sce_node;
  eng::scene::Database* sce_database;
  eng::scene::World* sce_world;
  eng::cam::Control* cam_control;
};

}
