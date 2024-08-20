#pragma once

#include <Base/Entity/Glyph.h>


namespace dat::glyph::object{

class Normal : public dat::base::Glyph
{
public:
  //Constructor / Destructor
  Normal();
  ~Normal();

public:
  //Main function
  void create();
  void update_pose(dat::base::Entity* entity);
  void update_glyph(dat::base::Entity* entity);

  //Construct
  void construct(dat::base::Entity* entity);
  glm::vec4 generate_random();

  inline int* get_size(){return &size;}

private:
  glm::vec4 color;
  int width;
  int size;
};

}
