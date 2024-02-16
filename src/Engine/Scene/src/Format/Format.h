#pragma once

#include <Utility/Specific/common.h>

namespace format::obj{class Importer;}
namespace format::csv{class Importer;}
namespace format::ply{class Importer;}
namespace format::pts{class Importer;}
namespace format::ptx{class Importer;}
namespace format::xyz{class Importer;}


namespace eng::scene{

class Format
{
public:
  //Constructor / Destructor
  Format();
  ~Format();

public:
  //Main function
  utl::media::File* import_data_from_path(std::string path);

  //Subfunction
  void insert_importer(utl::type::Importer* importer);
  bool is_format_supported(string format);

private:
  vector<utl::type::Importer*> vec_importer;
};

}
