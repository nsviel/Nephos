#pragma once

#include <IO/Base/Importer.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <tins/tins.h>
#include <iostream>
#include <stddef.h>
#include <bitset>

namespace vld{class Node;}
namespace vld{class Structure;}
namespace vld::processing{class Player;}
namespace vld::main{class Playback;}


namespace vld::utils{

enum Lidar{
  VLP_16 = 0,
  HDL_32 = 1,
};

class Importer : public io::base::Importer
{
public:
  //Constructor / Destructor
  Importer(vld::Node* node_velodyne);
  ~Importer();

public:
  //Main function
  std::shared_ptr<utl::base::Element> import(utl::base::Path path);

  //Subfunction
  void importer_init(std::string path);
  void importer_sniffing(std::string path);
  void importer_parsing(std::shared_ptr<dat::base::Set> dataset, std::string path);

  void parser_vlp16(std::shared_ptr<dat::base::Set> dataset, std::string path);
  void parser_hdl32(std::shared_ptr<dat::base::Set> dataset, std::string path);
  int get_file_length(std::string path);

  inline void set_lidar_model(int value){this->lidar_model = value;}
  inline bool* get_packet_range_on(){return &packet_range_on;}
  inline int* get_packet_beg(){return &packet_beg;}
  inline int* get_packet_end(){return &packet_end;}

private:
  vld::Structure* vld_struct;
  vld::processing::Player* vld_player;
  vld::main::Playback* vld_playback;

  bool packet_range_on;
  int lidar_model;
  int packet_beg;
  int packet_end;
};

}
