#pragma once

#include "../../Base/struct_voxelMap.h"
#include "../../../../Scene/Glyph/Base/Glyph_source.h"


namespace slam::glyph{

class Localmap : public Glyph_source
{
public:
  //Constructor / Destructor
  Localmap();
  ~Localmap();

public:
  void clear();
  void create_localmap();
  void create_localcloud();
  void update_localmap(slamap* map);
  void update_localcloud(slamap* map);

  inline Glyph* get_localmap(){return localmap;}
  inline Glyph* get_localcloud(){return localcloud;}

private:
  Glyph* localmap;
  Glyph* localcloud;

  glm::vec4 color;
};

}
