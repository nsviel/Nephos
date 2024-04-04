#pragma once

#include <Utility/Specific/Common.h>

namespace eng::scene{class Node;}
namespace vk::main{class Info;}
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
  Format(eng::scene::Node* node_scene);
  ~Format();

public:
  //Main function
  utl::file::Data* import_from_path(utl::file::Path path);
  void insert_from_path(utl::file::Path path, utl::type::Set* set);

  //Subfunction
  void insert_importer(utl::type::Importer* importer);
  void insert_exporter(utl::type::Exporter* exporter);
  bool is_format_supported(string format);
  void display_supported_format();

private:
  vk::main::Info* vk_info;

  vector<utl::type::Importer*> vec_importer;
  vector<utl::type::Exporter*> vec_exporter;
};

}
