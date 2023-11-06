#ifndef NODE_SCENE_H
#define NODE_SCENE_H

class Engine;
class Scene;
class ENG_database;
class Glyphs;
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
  inline Scene* get_sceneManager(){return sceneManager;}
  inline ENG_database* get_eng_database(){return eng_database;}
  inline Loader* get_loaderManager(){return loaderManager;}

private:
  Engine* engine;
  Scene* sceneManager;
  ENG_database* eng_database;
  Glyphs* glyphManager;
  Loader* loaderManager;
};

#endif
