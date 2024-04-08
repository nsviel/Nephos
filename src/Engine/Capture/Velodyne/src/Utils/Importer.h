#pragma once

#include <Utility/Specific/Common.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <tins/tins.h>
#include <iostream>
#include <stddef.h>
#include <bitset>

namespace vld::main{class Player;}
namespace vld::structure{class Main;}


namespace vld::utils{

enum Lidar{
  VLP_16 = 0,
  HDL_32 = 1,
};

class Importer : public utl::type::Importer
{
public:
  //Constructor / Destructor
  Importer(vld::structure::Main* vld_struct);
  ~Importer();

public:
  //Main function
  utl::File* import(utl::Path path);
  void insert(utl::type::Set* set);

  //Subfunction
  void importer_init(std::string path);
  void importer_sniffing(std::string path);
  void importer_parsing(utl::file::Dataset* dataset, std::string path);

  void parser_vlp16(utl::file::Dataset* dataset, std::string path);
  void parser_hdl32(utl::file::Dataset* dataset, std::string path);
  int get_file_length(std::string path);

  inline void set_lidar_model(int value){this->lidar_model = value;}
  inline bool* get_packet_range_on(){return &packet_range_on;}
  inline int* get_packet_beg(){return &packet_beg;}
  inline int* get_packet_end(){return &packet_end;}

private:
  vld::structure::Main* vld_struct;
  vld::main::Player* vld_player;

  bool packet_range_on;
  int lidar_model;
  int packet_beg;
  int packet_end;
};

}
