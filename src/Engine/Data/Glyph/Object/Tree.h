#pragma once

#include <Engine/Operation/Namespace.h>
#include "../Base/Glyph_source.h"


class Tree : public Glyph_source
{
public:
  //Constructor / Destructor
  Tree();
  ~Tree();

public:
  eng::structure::Glyph* create_glyph(eng::structure::Object* object);
  void update_tree(eng::structure::Object* object, eng::structure::Glyph* glyph);

  inline bool* get_visibility(){return &is_visible;}
  inline int* get_tree_level(){return &tree_level;}

private:
  eng::ope::Octree* octreeManager;
  bool is_visible;
  vec4 tree_color;
  int tree_level;
};
