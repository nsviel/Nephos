#pragma once

#include "../../../../Scene/Glyph/Base/Glyph_source.h"


namespace slam::glyph{

class Trajectory : public Glyph_source
{
public:
  //Constructor / Destructor
  Trajectory();
  ~Trajectory();

public:
  void create();
  void update(Collection* collection);
  void reset();

  inline Glyph* get_glyph(){return trajectory;}

private:
  Glyph* trajectory;

  glm::vec4 color;
  int width;
};

}
