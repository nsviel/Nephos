#include "ENG_data.h"
#include "ENG_scene/ENG_scene.h"
#include "ENG_scene/ENG_database.h"
#include "ENG_glyph/ENG_glyph.h"
#include "ENG_load/ENG_loader.h"


//Constructor / Destructor
ENG_data::ENG_data(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->eng_database = new ENG_database(this);
  this->eng_scene = new ENG_scene(this);
  this->eng_glyph = new ENG_glyph(this);
  this->eng_loader = new ENG_loader(this);

  //---------------------------
}
ENG_data::~ENG_data(){
  //---------------------------

  delete eng_scene;
  delete eng_database;
  delete eng_glyph;
  delete eng_loader;

  //---------------------------
}

void ENG_data::init(){
  //---------------------------

  eng_scene->init_set();
  eng_scene->init_scene();
  eng_glyph->create_glyph_scene();

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
