#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace utl::base{class Data;}

// Server side implementation of UDP client-server model


namespace vld::parser{

class HDL32
{
public:
  //Constructor / Destructor
  HDL32();
  ~HDL32();

public:
  //Main function
  utl::base::Data* parse_packet(std::vector<int> packet);

  //Subfunctions
  void parse_vector(std::vector<int> packet);
  void parse_blocks();
  void parse_azimuth();
  void parse_coordinates();
  void parse_timestamp();
  void final_check(utl::base::Data* cloud);

  //Subsubfunctions
  std::vector<float> calc_timing_offsets();
  void make_supressElements(std::vector<glm::vec3>& vec, std::vector<int> idx);
  void make_supressElements(std::vector<float>& vec, std::vector<int> idx);

private:
  std::vector<std::vector<int>> blocks;
  std::vector<glm::vec3> packet_xyz;
  std::vector<float> packet_R;
  std::vector<float> packet_I;
  std::vector<float> packet_A;
  std::vector<float> packet_t;

  float packet_ts_us;
  bool supress_emptyElements;
  int nb_laser;
  int nb_sequences;
};

}
