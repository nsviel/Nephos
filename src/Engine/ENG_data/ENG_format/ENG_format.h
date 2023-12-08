#ifndef FORMAT_H
#define FORMAT_H

#include <UTL_base/Struct_file.h>
#include <string>

class PLY_importer;
class OBJ_importer;
class CSV_importer;
class PCAP_importer;
class PTS_importer;
class PTX_importer;
class XYZ_importer;


class ENG_format
{
public:
  //Constructor / Destructor
  ENG_format();
  ~ENG_format();

public:
  data::File* get_data_from_file(std::string path);

private:
  PLY_importer* ply_import;
  OBJ_importer* obj_import;
  CSV_importer* csv_import;
  PCAP_importer* pcap_import;
  PTS_importer* pts_import;
  PTX_importer* ptx_import;
  XYZ_importer* xyz_import;
};

#endif
