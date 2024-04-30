#pragma once

#include <Data/src/Base/Glyph.h>


namespace dat::glyph::object{

class Normal : public dat::base::Glyph
{
public:
  //Constructor / Destructor
  Normal(eng::Node* node_engine);
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
  bool visibility;
  vec4 color;
  int width;
  int size;
};

}
