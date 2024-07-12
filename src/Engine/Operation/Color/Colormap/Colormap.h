#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>


namespace ope::color{

class Colormap
{
public:
  //Constructor / Destructor
  Colormap();
  ~Colormap();

public:
  void init();
  void choose(std::string name);
  glm::vec4 random();

  inline std::vector<glm::vec3>& get_colormap_selected(){return colormap_selected;}

private:
  std::vector<std::string> colormap_name;
  std::vector<std::vector<glm::vec3>> colormap_list;
  std::vector<glm::vec3> colormap_selected;
};

}
