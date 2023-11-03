#ifndef NODE_SCENE_H
#define NODE_SCENE_H

class Engine;
class Scene;
class Database;
class Glyphs;
class Loader;


class Data
{
public:
  //Constructor / Destructor
  Data(Engine* engine);
  ~Data();

public:
  void init();
  void reset();

  inline Engine* get_engine(){return engine;}
  inline Scene* get_sceneManager(){return sceneManager;}
  inline Database* get_dataManager(){return dataManager;}
  inline Loader* get_loaderManager(){return loaderManager;}

private:
  Engine* engine;
  Scene* sceneManager;
  Database* dataManager;
  Glyphs* glyphManager;
  Loader* loaderManager;
};

#endif
