#pragma once

#include <IO/src/Import/Structure/Base.h>
#include <IO/src/Import/Structure/Buffer.h>
#include <IO/src/Import/Structure/Configuration.h>
#include <Utility/Function/File/Path.h>
#include <Utility/Function/Math/Operation.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <stdint.h>
#include <cstdint>

namespace utl::base{class Attribut;}


namespace fmt::ply::importer{

class Binary
{
public:
  //Constructor / Destructor
  Binary();
  ~Binary();

public:
  //Main function
  void parse_binary(io::importer::Configuration* config, dat::base::Object* object);

  //Subfunction
  void pass_header(std::ifstream& file);
  void parse_vertex_little_endian(io::importer::Configuration* config, std::ifstream& file);
  void parse_face_little_endian(io::importer::Configuration* config, std::ifstream& file);
  void parse_vertex_big_endian(io::importer::Configuration* config, std::ifstream& file);
  void parse_face_big_endian(io::importer::Configuration* config, std::ifstream& file);
  void reorder_by_timestamp(utl::base::Data* data);
  int get_property_id(io::importer::Configuration* config, io::importer::Field field);

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
  utl::base::Attribut* utl_attribut;

  io::importer::Buffer buffer;
};

}
