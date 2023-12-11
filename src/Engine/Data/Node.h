#pragma once

class Engine;
class ENG_scene;
class Nodebase;
class ENG_glyph;
class ENG_loader;


namespace eng::data{

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
  inline ENG_scene* get_eng_scene(){return eng_scene;}
  inline Nodebase* get_eng_database(){return eng_database;}
  inline ENG_loader* get_eng_loader(){return eng_loader;}

private:
  Engine* engine;
  ENG_scene* eng_scene;
  Nodebase* eng_database;
  ENG_glyph* eng_glyph;
  ENG_loader* eng_loader;
};

}
