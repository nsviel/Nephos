#include "Base_glyph.h"

#include <Utility/Function/Math/fct_math.h>


namespace eng::data{

//Constructor / Destructor
Glyph::Glyph(){
  //---------------------------

  this->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  this->is_visible = true;
  this->type = "Glyph";

  //---------------------------
}
Glyph::~Glyph(){}



}
