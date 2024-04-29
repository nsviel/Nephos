#pragma once

#include <Data/base/Glyph.h>


namespace cam::glyph{

class Target : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Target(eng::Node* node_engine);
  ~Target();

public:
  void create();
  void update_pose(utl::type::Entity* entity);

  //Subfunction
  void construct();

private:
  float scale;
};

}
