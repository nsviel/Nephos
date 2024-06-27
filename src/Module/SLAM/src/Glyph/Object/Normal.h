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
  void update_normal_cloud(Cloud* cloud, std::vector<glm::vec3>& xyz_s, std::vector<glm::vec3>& Nxyz_s);

  inline int* get_size(){return &size;}

private:
  bool visibility;
  glm::vec4 color;
  int size;
  int width;
};

}
