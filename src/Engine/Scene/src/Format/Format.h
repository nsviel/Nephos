#pragma once

#include <Utility/Specific/common.h>

namespace format::obj{class Importer;}
namespace format::csv{class Importer;}
namespace format::ply{class Importer;}
namespace format::pts{class Importer;}
namespace format::ptx{class Importer;}
namespace format::xyz{class Importer;}


using MyFile = utl::media::File;


namespace eng::scene{

class Format
{
public:
  //Constructor / Destructor
  Format();
  ~Format();

public:
  //Main function
  MyFile* get_data_from_file(std::string path);

  //Subfunction
  bool is_format_supported(string format);

private:
  format::ply::Importer* ply_import;
  format::obj::Importer* obj_import;
  format::csv::Importer* csv_import;
  format::pts::Importer* pts_import;
  format::ptx::Importer* ptx_import;
  format::xyz::Importer* xyz_import;

  vector<string> supported_format;
};

}
