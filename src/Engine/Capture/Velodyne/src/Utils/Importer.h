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

namespace vld{class Player;}
namespace vld::structure{class Main;}


namespace vld{

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
  utl::file::Data* import(utl::file::Path path);
  void insert(utl::type::Set* set);

  //Subfunction
  void importer_init(std::string path);
  void importer_sniffing(std::string path);
  void importer_parsing(utl::file::Set* set, std::string path);

  void parser_vlp16(utl::file::Set* set, std::string pathFile);
  void parser_hdl32(utl::file::Set* set, std::string pathFile);
  int get_file_length(std::string pathFile);

  inline void set_lidar_model(int value){this->lidar_model = value;}
  inline bool* get_packet_range_on(){return &packet_range_on;}
  inline int* get_packet_beg(){return &packet_beg;}
  inline int* get_packet_end(){return &packet_end;}

private:
  vld::structure::Main* vld_struct;
  vld::Player* vld_player;

  bool packet_range_on;
  int lidar_model;
  int packet_beg;
  int packet_end;
};

}
