#pragma once

#include <Utility/Specific/Common.h>

namespace ldr{class Node;}
namespace vk::main{class Interface;}
namespace format::obj{class Importer;}
namespace format::csv{class Importer;}
namespace format::ply{class Importer;}
namespace format::pts{class Importer;}
namespace format::ptx{class Importer;}
namespace format::xyz{class Importer;}
namespace format::ply{class Exporter;}
namespace ldr::base{class Importer;}
namespace ldr::base{class Exporter;}
namespace utl::type{class Set;}


namespace ldr{

class Format
{
public:
  //Constructor / Destructor
  Format(ldr::Node* node_loader);
  ~Format();

public:
  //Main function
  utl::File* import_from_path(utl::Path path);
  void insert_from_path(utl::Path path, utl::type::Set* set);

  //Subfunction
  void insert_importer(ldr::base::Importer* importer);
  void insert_exporter(ldr::base::Exporter* exporter);
  bool is_format_supported(string format);
  void display_supported_format();

private:
  vk::main::Interface* vk_interface;

  vector<ldr::base::Importer*> vec_importer;
  vector<ldr::base::Exporter*> vec_exporter;
};

}
