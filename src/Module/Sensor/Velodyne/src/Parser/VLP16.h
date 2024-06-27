#pragma once

// Server side implementation of UDP client-server model

#include <Utility/Specific/Common.h>


namespace vld::parser{

class VLP16
{
public:
  //Constructor / Destructor
  VLP16();
  ~VLP16();

public:
  //Main function
  utl::base::Data* parse_packet(std::vector<int> packet);

  //Subfunctions
  bool parse_header(std::vector<int>& packet_dec);
  void parse_vector(std::vector<int> packet);
  void parse_blocks();
  void parse_azimuth();
  void parse_coordinates();
  void parse_timestamp();

  //Final processing function
  void reorder_by_azimuth(utl::base::Data* cloud);
  void supress_empty_data();

  //Subsubfunctions
  std::vector<float> calc_timing_offsets();
  void make_supressElements(std::vector<vec3>& vec, vector<int> idx);
  void make_supressElements(std::vector<float>& vec, vector<int> idx);

private:
  std::vector<vector<int>> blocks;
  std::vector<vec3> packet_xyz;
  std::vector<float> packet_R;
  std::vector<float> packet_I;
  std::vector<float> packet_A;
  std::vector<float> packet_t;

  int nb_laser;
  int nb_sequences;
  float packet_ts_us;
  bool supress_emptyElements;
};

}
