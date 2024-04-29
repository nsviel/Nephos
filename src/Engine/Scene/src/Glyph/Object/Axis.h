#pragma once

#include <Operation/Namespace.h>
#include <Scene/src/Base/Glyph.h>


namespace glyph::object{

class Axis : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Axis(eng::Node* node_engine);
  ~Axis();

public:
  //Main function
  void create();
  void update_pose(utl::type::Entity* entity);

  //Subfunctions
  void construct();

private:
  ope::Transformation* ope_transform;

  bool is_visible;
};

}
