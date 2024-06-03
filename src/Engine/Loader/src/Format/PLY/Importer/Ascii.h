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

  //Subfunction
  void parse_data(std::ifstream& file, utl::base::Data* data);
  void parse_data_withface(std::ifstream& file, utl::base::Data* data);
  int get_property_id(format::ply::Field field);

private:
  std::vector<format::ply::Property> vec_property;
  int file_format;
  int point_data_idx;
  int point_number;
  int face_number;
  int header_size;
};

}
