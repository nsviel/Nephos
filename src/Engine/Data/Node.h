#pragma once

#include <Engine/Data/Namespace.h>

class Engine;

class ENG_glyph;
class ENG_loader;


namespace eng::data{
  class ENG_scene;
  class ENG_database;

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
  inline eng::data::ENG_scene* get_eng_scene(){return eng_scene;}
  inline eng::data::ENG_database* get_eng_database(){return eng_database;}
  inline ENG_loader* get_eng_loader(){return eng_loader;}

private:
  Engine* engine;
  eng::data::ENG_scene* eng_scene;
  eng::data::ENG_database* eng_database;
  ENG_glyph* eng_glyph;
  ENG_loader* eng_loader;
};

}
