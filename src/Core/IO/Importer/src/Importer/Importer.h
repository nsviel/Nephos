#pragma once

#include <memory>
#include <string>
#include <vector>

namespace dat::base{class Set;}
namespace dat::base{class Object;}
namespace utl::base{class Data;}
namespace utl::base{class Element;}
namespace utl::base{class Path;}
namespace utl::base{class Thread;}
namespace io::imp{class Node;}
namespace io::imp{class Structure;}
namespace io::imp{class Operation;}
namespace io::base{class Importer;}


namespace io::imp{

class Importer
{
public:
  //Constructor / Destructor
  Importer(io::imp::Node* node_importer);
  ~Importer();

public:
  //Main function
  void insert_importer(io::base::Importer* importer);
  std::shared_ptr<utl::base::Element> import_from_path(utl::base::Path path);

  //Subfunction
  bool is_format_supported(std::string format);
  std::vector<std::string> get_supported_format();

private:
  io::imp::Structure* io_struct;
  io::imp::Operation* io_operation;

  std::vector<io::base::Importer*> vec_importer;
};

}
