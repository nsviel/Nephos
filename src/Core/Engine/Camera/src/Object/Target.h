#pragma once

#include <Data/Base/Entity/Glyph.h>


namespace cam::glyph{

class Target : public dat::base::Glyph
{
public:
  //Constructor / Destructor
  Target();
  ~Target();

public:
  void create();
  void update_pose(dat::base::Entity* entity);

  //Subfunction
  void construct();

private:
  float scale;
};

}
