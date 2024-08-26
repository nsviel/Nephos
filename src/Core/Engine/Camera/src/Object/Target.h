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
  void update_pose(std::shared_ptr<dat::base::Entity> entity);

  //Subfunction
  void construct();

private:
  float scale;
};

}
