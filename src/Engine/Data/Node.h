#pragma once

#include <Engine/Data/Namespace.h>

class Engine;

namespace eng::scene{
class Scene;
class Database;
class Loader;
class Glyph;


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
  inline eng::scene::Scene* get_eng_scene(){return eng_scene;}
  inline eng::scene::Database* get_eng_database(){return eng_database;}
  inline eng::scene::Loader* get_eng_loader(){return eng_loader;}
  inline eng::scene::Glyph* get_eng_glyph(){return eng_glyph;}

private:
  Engine* engine;
  eng::scene::Scene* eng_scene;
  eng::scene::Database* eng_database;
  eng::scene::Glyph* eng_glyph;
  eng::scene::Loader* eng_loader;
};

}
