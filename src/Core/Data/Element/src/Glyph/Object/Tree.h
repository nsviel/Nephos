#pragma once

#include <Engine/Operation/Namespace.h>
#include <Base/Entity/Glyph.h>


namespace dat::glyph::object{

class Tree : public dat::base::Glyph
{
public:
  //Constructor / Destructor
  Tree();
  ~Tree();

public:
  //Main function
  void create();
  void update_glyph(utl::base::Data* data);

  inline int* get_level(){return &level;}

private:
  ope::tree::Octree* octreeManager;
  int level;
};

}
