#pragma once

#include "../../../../Scene/Glyph/Base/Glyph_source.h"


namespace slam::glyph{

class Car : public Glyph_source
{
public:
  Car();

public:
  void create_glyph();
  void update_glyph(Collection* collection);
  void reset_glyph();

private:
  float lidar_height;
  int width;
};

}
