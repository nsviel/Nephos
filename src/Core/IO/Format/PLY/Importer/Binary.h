#pragma once

#include <Importer/src/Structure/Base.h>
#include <Importer/src/Structure/Buffer.h>
#include <Importer/src/Structure/Configuration.h>
#include <Utility/Function/File/Path.h>
#include <Utility/Function/Math/Operation.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <stdint.h>
#include <cstdint>

namespace dat::atr{class Field;}


namespace fmt::ply::importer{

class Binary
{
public:
  //Constructor / Destructor
  Binary();
  ~Binary();

public:
  //Main function
  void parse_binary(io::imp::Configuration* config, dat::base::Object* object);

  //Subfunction
  void pass_header(std::ifstream& file);
  void parse_vertex_little_endian(io::imp::Configuration* config, std::ifstream& file);
  void parse_face_little_endian(io::imp::Configuration* config, std::ifstream& file);
  void parse_vertex_big_endian(io::imp::Configuration* config, std::ifstream& file);
  void parse_face_big_endian(io::imp::Configuration* config, std::ifstream& file);
  void reorder_by_timestamp(utl::base::Data* data);
  int get_property_id(io::imp::Configuration* config, io::imp::Field field);

  //Binary type
  float reverse_float(const float inFloat);
  int reverse_int(const int inInt);
  float get_float_from_binary(char* data, int& offset);
  float get_double_from_binary(char* block_data, int& offset);
  float get_int_from_binary(char* data, int& offset);
  float get_uint8_from_binary(char* block_data, int& offset);
  float get_uint16_from_binary(char* block_data, int& offset);
  float get_uint32_from_binary(char* block_data, int& offset);
  float get_uchar_from_binary(char* block_data, int& offset);
  float get_ushort_from_binary(char* block_data, int& offset);

private:
  dat::atr::Field* atr_field;

  io::imp::Buffer buffer;
};

}
