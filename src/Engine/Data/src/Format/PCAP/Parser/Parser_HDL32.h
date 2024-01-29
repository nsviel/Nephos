#pragma once

// Server side implementation of UDP client-server model

#include <Utility/Specific/common.h>
#include <Utility/Function/Math/Math.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <chrono>


class Parser_HDL32
{
public:
  //Constructor / Destructor
  Parser_HDL32();
  ~Parser_HDL32();

public:
  //Main functions
  utl::media::File* parse_packet(std::vector<int> packet);

  //Subfunctions
  void parse_vector(std::vector<int> packet);
  void parse_blocks();
  void parse_azimuth();
  void parse_coordinates();
  void parse_timestamp();
  void final_check(utl::media::File* cloud);

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

  int nb_laser;
  int nb_sequences;
  float packet_ts_us;
  bool supress_emptyElements;
};
