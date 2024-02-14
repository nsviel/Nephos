#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/File/Info.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>


namespace format::ply{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter();
  ~Exporter();

public:
  //Main functions
  bool export_cloud(utl::entity::Object* object, std::string path_dir, std::string ply_format);

private:
  std::vector<std::string> property_type;
  std::vector<std::string> property_name;
  std::vector<int> property_size;
  std::string format;
  bool is_timestamp;
  bool is_intensity;
  bool is_normal;
  bool is_color;
  int point_data_idx;
  int point_number;
  int face_number;
  int property_number;
  int header_size;
};

}
