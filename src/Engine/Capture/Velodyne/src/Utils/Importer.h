#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/File/Info.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <tins/tins.h>
#include <iostream>
#include <stddef.h>
#include <bitset>


namespace velodyne{

class Importer : public utl::type::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main function
  utl::file::Set* import(std::string pathFile);

  //Subfunction
  void importer_init(std::string path);
  void importer_sniffing(std::string path);
  void importer_parsing(utl::file::Set* set, std::string path);
  
  void loader_vlp16(utl::file::Set* set, std::string pathFile);
  void loader_hdl32(utl::file::Set* set, std::string pathFile);
  int get_file_length(std::string pathFile);

  inline void set_lidar_model(std::string value){this->LiDAR_model = value;}
  inline bool* get_packet_range_on(){return &packet_range_on;}
  inline int* get_packet_beg(){return &packet_beg;}
  inline int* get_packet_end(){return &packet_end;}

private:
  std::string LiDAR_model;
  bool packet_range_on;
  int packet_beg;
  int packet_end;
};

}
