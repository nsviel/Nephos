#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/File/Info.h>
#include <Utility/Function/Math/Math.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <stdint.h>
#include <cstdint>


namespace format::ply{

class Importer : public utl::type::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main functions
  utl::file::Entity* import(std::string path_file);

private:
  //Loader data
  void Loader_header(std::string path);
  void Loader_ascii(std::ifstream& file, utl::file::Entity* entity);
  void Loader_ascii_withface(std::ifstream& file, utl::file::Entity* entity);
  void Loader_bin_little_endian(std::ifstream& file, utl::file::Entity* entity);
  void Loader_bin_little_endian_withface(std::ifstream& file, utl::file::Entity* entity);
  void Loader_bin_big_endian(std::ifstream& file, utl::file::Entity* entity);
  void Loader_bin_big_endian_withface(std::ifstream& file, utl::file::Entity* entity);

  //Loader subfunctions
  float reverse_float(const float inFloat);
  int reverse_int(const int inInt);
  void reorder_by_timestamp(utl::file::Entity* entity);
  int get_id_property(std::string name);
  float get_float_from_binary(char* data, int& offset);
  float get_double_from_binary(char* block_data, int& offset);
  float get_int_from_binary(char* data, int& offset);
  float get_uint8_from_binary(char* block_data, int& offset);
  float get_uint16_from_binary(char* block_data, int& offset);
  float get_uint32_from_binary(char* block_data, int& offset);
  float get_uchar_from_binary(char* block_data, int& offset);

private:
  std::vector<std::string> property_type;
  std::vector<std::string> property_name;
  std::vector<int> property_size;
  std::string property_format;
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
