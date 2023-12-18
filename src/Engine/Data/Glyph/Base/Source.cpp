#include "Source.h"


namespace glyph::base{

//Constructor / destructor
Source::Source(){
  //---------------------------

  this->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  this->is_visible = true;

  //---------------------------
}
Source::~Source(){
  //---------------------------

  delete glyph;

  //---------------------------
}

}
