#pragma once

#include "../../../../Scene/Glyph/Base/Glyph_source.h"


namespace slam::glyph{

class Keypoint : public Glyph_source
{
public:
  Keypoint();

public:
  void create_glyph(Cloud* cloud);
  void update_keypoint_location(Cloud* cloud);
  void update_keypoint_normal(Cloud* cloud);

private:
};

}
