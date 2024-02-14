#pragma once

#include <Utility/Specific/common.h>

namespace format::obj{class Importer;}
class PLY_importer;
class CSV_importer;
class PCAP_importer;
class PTS_importer;
class PTX_importer;
class XYZ_importer;

using MyFile = utl::media::File;


namespace eng::scene{

class Format
{
public:
  //Constructor / Destructor
  Format();
  ~Format();

public:
  MyFile* get_data_from_file(std::string path);

private:
  PLY_importer* ply_import;
  format::obj::Importer* obj_import;
  CSV_importer* csv_import;
  PCAP_importer* pcap_import;
  PTS_importer* pts_import;
  PTX_importer* ptx_import;
  XYZ_importer* xyz_import;
};

}
