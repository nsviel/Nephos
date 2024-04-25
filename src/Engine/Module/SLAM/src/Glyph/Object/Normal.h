#pragma once

#include "../../../../Scene/Glyph/Base/Glyph_source.h"


namespace slam::glyph{

class Normal : public Glyph_source
{
public:
  //Constructor / Destructor
  Normal();
  ~Normal();

public:
  void create_glyph(Cloud* cloud);
  void update_normal_cloud(Cloud* cloud);
  void update_normal_cloud(Cloud* cloud, vector<vec3>& xyz_s, vector<vec3>& Nxyz_s);

  inline int* get_size(){return &size;}

private:
  bool visibility;
  vec4 color;
  int size;
  int width;
};

}
