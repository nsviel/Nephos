#pragma once

#include <Loader/src/Format/PLY/Utils.h>
#include <Loader/src/Base/Importer.h>
#include <Utility/Function/File/Path.h>
#include <Utility/Function/Math/Math.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <stdint.h>
#include <cstdint>


namespace format::ply::importer{

class Ascii
{
public:
  //Constructor / Destructor
  Ascii();
  ~Ascii();

public:
  //Main function
  void parse_ascii(dat::base::Object* object, format::ply::Header* header);

  //Parser
  void parse_vertice(std::ifstream& file, format::ply::Header* header);
  void parse_data_withface(std::ifstream& file, utl::base::Data* data);

  //Subfunction
  void pass_header(std::ifstream& file);
  int get_property_id(format::ply::Header* header, format::ply::Field field);

private:
  std::vector<glm::vec3> vertex;
  std::vector<glm::vec3> normal;
  std::vector<float> intensity;
};

}
