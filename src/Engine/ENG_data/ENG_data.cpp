#include "ENG_data.h"
#include "ENG_scene/ENG_scene.h"
#include "ENG_scene/ENG_database.h"
#include "Glyph/Glyphs.h"
#include "Load/Loader.h"


//Constructor / Destructor
ENG_data::ENG_data(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->eng_database = new ENG_database(this);
  this->eng_scene = new ENG_scene(this);
  this->glyphManager = new Glyphs(this);
  this->loaderManager = new Loader(this);

  //---------------------------
}
ENG_data::~ENG_data(){
  //---------------------------

  delete eng_scene;
  delete eng_database;
  delete glyphManager;
  delete loaderManager;

  //---------------------------
}

void ENG_data::init(){
  //---------------------------

  eng_scene->init_set();
  eng_scene->init_scene();
  glyphManager->create_glyph_scene();

  //---------------------------
}
void ENG_data::reset(){
  //---------------------------

  eng_scene->reset_scene();

  //---------------------------
}
void ENG_data::loop(){
  //---------------------------

  eng_scene->loop();

  //---------------------------
}
