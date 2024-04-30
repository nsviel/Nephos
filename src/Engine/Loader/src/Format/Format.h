#pragma once

#include <vector>
#include <string>

namespace vk::main{class Interface;}
namespace dat::base{class Set;}
namespace utl::media{class File;}
namespace utl::media{class Path;}
namespace ldr{class Node;}
namespace ldr::base{class Importer;}
namespace ldr::base{class Exporter;}


namespace ldr{

class Format
{
public:
  //Constructor / Destructor
  Format(ldr::Node* node_loader);
  ~Format();

public:
  //Main function
  utl::media::File* import_from_path(utl::media::Path path);
  void insert_from_path(utl::media::Path path, dat::base::Set* set);

  //Subfunction
  void insert_importer(ldr::base::Importer* importer);
  void insert_exporter(ldr::base::Exporter* exporter);
  bool is_format_supported(std::string format);
  void display_supported_format();

private:
  vk::main::Interface* vk_interface;

  std::vector<ldr::base::Importer*> vec_importer;
  std::vector<ldr::base::Exporter*> vec_exporter;
};

}
