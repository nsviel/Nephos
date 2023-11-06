#include "ENG_data.h"
#include "Scene/Scene.h"
#include "Scene/Database.h"
#include "Glyph/Glyphs.h"
#include "Load/Loader.h"


//Constructor / Destructor
ENG_data::ENG_data(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->dataManager = new Database(this);
  this->sceneManager = new Scene(this);
  this->glyphManager = new Glyphs(this);
  this->loaderManager = new Loader(this);

  //---------------------------
}
ENG_data::~ENG_data(){
  //---------------------------

  delete sceneManager;
  delete dataManager;
  delete glyphManager;
  delete loaderManager;

  //---------------------------
}

void ENG_data::init(){
  //---------------------------

  sceneManager->init_set();
  sceneManager->init_scene();
  glyphManager->create_glyph_scene();

  //---------------------------
}
void ENG_data::reset(){
  //---------------------------

  sceneManager->reset_scene();

  //---------------------------
}
void ENG_data::loop(){
  //---------------------------

  sceneManager->loop();

  //---------------------------
}
