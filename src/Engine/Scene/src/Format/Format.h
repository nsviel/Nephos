#pragma once

#include <Utility/Specific/common.h>

namespace format::obj{class Importer;}
namespace format::csv{class Importer;}
namespace format::ply{class Importer;}
namespace format::pts{class Importer;}
namespace format::ptx{class Importer;}
namespace format::xyz{class Importer;}
namespace format::ply{class Exporter;}


namespace eng::scene{

class Format
{
public:
  //Constructor / Destructor
  Format();
  ~Format();

public:
  //Main function
  utl::file::Data* import_from_path(utl::file::Path path);

  //Subfunction
  void insert_importer(utl::type::Importer* importer);
  void insert_exporter(utl::type::Exporter* exporter);
  bool is_format_supported(string format);
  void display_supported_format();

private:
  vector<utl::type::Importer*> vec_importer;
  vector<utl::type::Exporter*> vec_exporter;
};

}
