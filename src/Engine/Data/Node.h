#pragma once

#include <Engine/Data/Namespace.h>

class Engine;

namespace eng::data{
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
  inline eng::data::Scene* get_eng_scene(){return eng_scene;}
  inline eng::data::Database* get_eng_database(){return eng_database;}
  inline eng::data::Loader* get_eng_loader(){return eng_loader;}
  inline eng::data::Glyph* get_eng_glyph(){return eng_glyph;}

private:
  Engine* engine;
  eng::data::Scene* eng_scene;
  eng::data::Database* eng_database;
  eng::data::Glyph* eng_glyph;
  eng::data::Loader* eng_loader;
};

}
