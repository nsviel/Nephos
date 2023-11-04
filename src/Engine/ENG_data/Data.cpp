#include "Data.h"
#include "Scene/Scene.h"
#include "Scene/Database.h"
#include "Glyph/Glyphs.h"
#include "Load/Loader.h"


//Constructor / Destructor
Data::Data(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->dataManager = new Database(this);
  this->sceneManager = new Scene(this);
  this->glyphManager = new Glyphs(this);
  this->loaderManager = new Loader(this);

  //---------------------------
}
Data::~Data(){
  //---------------------------

  delete sceneManager;
  delete dataManager;
  delete glyphManager;
  delete loaderManager;

  //---------------------------
}

void Data::init(){
  //---------------------------

  sceneManager->init_set();
  sceneManager->init_scene();
  glyphManager->create_glyph_scene();

  //---------------------------
}
void Data::reset(){
  //---------------------------

  sceneManager->reset_scene();

  //---------------------------
}
void Data::loop(){
  //---------------------------

  sceneManager->loop();

  //---------------------------
}
