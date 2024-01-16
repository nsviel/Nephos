#include "Glyph.h"

#include <Engine/Engine.h>
#include <Utility/Function/Math/fct_math.h>


namespace eng::data{

//Constructor / Destructor
Glyph::Glyph(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  this->is_visible = true;
  this->type = "Glyph";

  //---------------------------
}
Glyph::~Glyph(){}



}
