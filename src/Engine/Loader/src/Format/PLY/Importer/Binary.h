#pragma once

#include <Loader/src/Format/PLY/Structure/Namespace.h>
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



namespace fmt::ply::importer{

class Binary
{
public:
  //Constructor / Destructor
  Binary();
  ~Binary();

public:
  //Main function
  void parse_binary(dat::base::Object* object, fmt::ply::Header* header);

  //Parser
  void parse_vertex_little_endian(std::ifstream& file);
  void parse_face_little_endian(std::ifstream& file);
  void parse_vertex_big_endian(std::ifstream& file);
  void parse_face_big_endian(std::ifstream& file);

  //Subfunction
  void pass_header(std::ifstream& file);
  float reverse_float(const float inFloat);
  int reverse_int(const int inInt);
  void reorder_by_timestamp(utl::base::Data* data);
  int get_property_id(fmt::ply::Field field);

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
  fmt::ply::Header* header = nullptr;
  utl::base::Data data;
};

}
