#pragma once

#include <Operation/Namespace.h>
#include <Data/base/Glyph.h>


namespace dat::glyph::object{

class Tree : public utl::entity::Glyph
{
public:
  //Constructor / Destructor
  Tree(eng::Node* node_engine);
  ~Tree();

public:
  //Main function
  void create();
  void update_glyph(utl::type::Data* data);

  inline int* get_level(){return &level;}

private:
  ope::tree::Octree* octreeManager;
  int level;
};

}
