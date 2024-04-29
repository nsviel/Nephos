#pragma once

#include <Utility/Specific/Common.h>

namespace sce{class Node;}
namespace vk::main{class Interface;}
namespace format::obj{class Importer;}
namespace format::csv{class Importer;}
namespace format::ply{class Importer;}
namespace format::pts{class Importer;}
namespace format::ptx{class Importer;}
namespace format::xyz{class Importer;}
namespace format::ply{class Exporter;}


namespace ldr{

class Format
{
public:
  //Constructor / Destructor
  Format(sce::Node* node_scene);
  ~Format();

public:
  //Main function
  utl::File* import_from_path(utl::Path path);
  void insert_from_path(utl::Path path, utl::type::Set* set);

  //Subfunction
  void insert_importer(utl::type::Importer* importer);
  void insert_exporter(utl::type::Exporter* exporter);
  bool is_format_supported(string format);
  void display_supported_format();

private:
  vk::main::Interface* vk_interface;

  vector<utl::type::Importer*> vec_importer;
  vector<utl::type::Exporter*> vec_exporter;
};

}
