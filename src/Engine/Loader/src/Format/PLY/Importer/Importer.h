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

namespace format::ply::importer{class Ascii;}
namespace format::ply::importer{class Binary;}


namespace format::ply{

class Importer : public ldr::base::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main functions
  utl::base::Element* import(utl::media::Path path);

private:
  //Header
  void parse_header(std::ifstream& file);
  void parse_header_format(std::string format);
  void parse_header_property(std::string type, std::string field);

  //ASCII
  void parse_ascii(std::ifstream& file, utl::file::Data* entity);
  void parse_ascii_withface(std::ifstream& file, utl::file::Data* entity);

  //Binary
  void parse_bin_little_endian(std::ifstream& file, utl::file::Data* entity);
  void parse_bin_little_endian_withface(std::ifstream& file, utl::file::Data* entity);
  void parse_bin_big_endian(std::ifstream& file, utl::file::Data* entity);
  void parse_bin_big_endian_withface(std::ifstream& file, utl::file::Data* entity);

  //Subfunction
  float reverse_float(const float inFloat);
  int reverse_int(const int inInt);
  void reorder_by_timestamp(utl::file::Data* entity);
  int get_property_id(format::ply::Field field);

  //Binary type
  float get_float_from_binary(char* data, int& offset);
  float get_double_from_binary(char* block_data, int& offset);
  float get_int_from_binary(char* data, int& offset);
  float get_uint8_from_binary(char* block_data, int& offset);
  float get_uint16_from_binary(char* block_data, int& offset);
  float get_uint32_from_binary(char* block_data, int& offset);
  float get_uchar_from_binary(char* block_data, int& offset);
  float get_ushort_from_binary(char* block_data, int& offset);

private:
  format::ply::importer::Ascii* ply_ascii;
  format::ply::importer::Binary* ply_binary;

  std::vector<format::ply::Property> vec_property;
  int file_format;
  int point_data_idx;
  int point_number;
  int face_number;
  int header_size;
};

}
