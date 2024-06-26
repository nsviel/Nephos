#pragma once

#include "../../../../Scene/Glyph/Base/Glyph_source.h"


namespace slam::glyph{

class Matching : public Glyph_source
{
public:
  //Constructor / Destructor
  Matching();
  ~Matching();

public:
  void create_glyph();
  void update_matching(std::vector<vec3>& xyz);
  void reset();

  inline Glyph* get_glyph(){return matching;}

private:
  Glyph* matching;
  vec4 color;
};

}
