#pragma once

#include <Data/Base/Entity/Glyph.h>


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
  void update_pose(std::shared_ptr<dat::base::Entity> entity);
  void update_glyph(std::shared_ptr<dat::base::Entity> entity);

  //Construct
  void construct(std::shared_ptr<dat::base::Entity> entity);
  glm::vec4 generate_random();

  inline int* get_size(){return &size;}

private:
  glm::vec4 color;
  int width;
  int size;
};

}
