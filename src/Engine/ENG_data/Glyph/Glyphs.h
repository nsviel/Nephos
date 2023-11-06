#ifndef GLYPHS_H
#define GLYPHS_H

#include "Base/Glyph_source.h"
#include <ELE_specific/common.h>

class ENG_data;
class Scene;


class Glyphs
{
public:
  //Constructor / Destructor
  Glyphs(ENG_data* eng_data);
  ~Glyphs();

public:
  //Main functions
  void create_glyph_scene();
  Glyph_source* get_glyph_src_byName(string name);

private:
  ENG_data* eng_data;
  Scene* sceneManager;

  vector<Glyph_source*> vec_glyph_src;
};

#endif
