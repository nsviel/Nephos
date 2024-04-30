#pragma once

#include <Data/src/Base/Glyph.h>


namespace cam::glyph{

class Target : public dat::base::Glyph
{
public:
  //Constructor / Destructor
  Target(eng::Node* node_engine);
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
