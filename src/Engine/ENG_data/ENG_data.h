#ifndef ENG_DATA_H
#define ENG_DATA_H

class Engine;
class ENG_scene;
class ENG_database;
class ENG_glyph;
class Loader;


class ENG_data
{
public:
  //Constructor / Destructor
  ENG_data(Engine* engine);
  ~ENG_data();

public:
  void init();
  void reset();
  void loop();

  inline Engine* get_engine(){return engine;}
  inline ENG_scene* get_eng_scene(){return eng_scene;}
  inline ENG_database* get_eng_database(){return eng_database;}
  inline Loader* get_loaderManager(){return loaderManager;}

private:
  Engine* engine;
  ENG_scene* eng_scene;
  ENG_database* eng_database;
  ENG_glyph* eng_glyph;
  Loader* loaderManager;
};

#endif
