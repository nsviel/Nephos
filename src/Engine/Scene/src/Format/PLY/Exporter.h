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
  void export(utl::type::Data* data, std::string path);
  void export_ascii(utl::type::Data* data, std::string path);

  //Subfunction
  void write_header(std::ofstream& file, std::string format, utl::type::Data* data);
  void write_data_ascii(std::ofstream& file, utl::type::Data* data);
  void write_data_binary(std::ofstream& file, utl::type::Data* data);

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
