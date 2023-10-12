#ifndef GLYPHS_H
#define GLYPHS_H

#include "Base/Glyph_source.h"
#include <Specific/common.h>

class Data;
class Scene;


class Glyphs
{
public:
  //Constructor / Destructor
  Glyphs(Data* data_node);
  ~Glyphs();

public:
  //Main functions
  void create_glyph_scene();
  Glyph_source* get_glyph_src_byName(string name);

private:
  Data* data_node;
  Scene* sceneManager;

  vector<Glyph_source*> vec_glyph_src;
};

#endif
