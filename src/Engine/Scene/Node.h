#pragma once

#include <Engine/Scene/Namespace.h>

class Engine;

namespace eng::scene{
class Scene;
class Database;
class Loader;
class Glyph;
class Operation;
class Bookmark;


class Node
{
public:
  //Constructor / Destructor
  Node(Engine* engine);
  ~Node();

public:
  void init();
  void reset();
  void loop();

  inline Engine* get_engine(){return engine;}
  inline eng::scene::Scene* get_scene(){return sce_scene;}
  inline eng::scene::Database* get_scene_database(){return sce_database;}
  inline eng::scene::Loader* get_scene_loader(){return sce_loader;}
  inline eng::scene::Glyph* get_scene_glyph(){return sce_glyph;}
  inline eng::scene::Bookmark* get_scene_bookmark(){return sce_bookmark;}

private:
  Engine* engine;
  eng::scene::Scene* sce_scene;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::scene::Loader* sce_loader;
  eng::scene::Bookmark* sce_bookmark;
};

}
