#pragma once

#include <Data/Base/Entity/Glyph.h>


namespace dat::glyph::object{

class AABB : public dat::base::Glyph
{
public:
  AABB();
  ~AABB();

public:
  //Main function
  void create();
  void update_glyph(utl::base::Pose& pose);

  //Subfunction
  std::vector<glm::vec3> build_box(glm::vec3 min, glm::vec3 max);

private:
  glm::vec4 color;
};

}
