#pragma once

#include <Utility/Specific/Common.h>


namespace ope::color{

class Colormap
{
public:
  //Constructor / Destructor
  Colormap();
  ~Colormap();

public:
  void init();
  void choose(string name);
  vec4 random();

  inline vector<vec3>& get_colormap_selected(){return colormap_selected;}

private:
  vector<string> colormap_name;
  vector<vector<vec3>> colormap_list;
  vector<vec3> colormap_selected;
};

}