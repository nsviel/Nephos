#pragma once

#include <Engine/Operation/Namespace.h>
#include <Data/Base/Entity/Glyph.h>
#include <memory>


namespace dat::glyph::object{

class Axis : public dat::base::Glyph
{
public:
  //Constructor / Destructor
  Axis();
  ~Axis();

public:
  //Main function
  void create();
  void update_pose(std::shared_ptr<dat::base::Entity> entity);

  //Subfunctions
  void construct();

private:
};

}
