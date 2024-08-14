#pragma once

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
namespace io::imp{class Base;}


namespace io::imp{

class Importer
{
public:
  //Constructor / Destructor
  Importer(io::imp::Node* node_importer);
  ~Importer();

public:
  //Main function
  utl::base::Data* load_data(std::string path);
  void load_set(utl::base::Path file_path);
  void load_directory(utl::base::Path path);
  void load_object(utl::base::Path file_path);
  void load_object(utl::base::Path file_path, utl::base::Path path_transfo);

  //Subfunction
  void init_path();
  void insert_importer(io::imp::Base* importer);
  bool check_path(std::string path);
  bool is_format_supported(std::string format);
  std::vector<std::string> get_supported_format();
  utl::base::Element* import_from_path(utl::base::Path path);

private:
  io::Structure* io_struct;
  io::imp::Operation* io_operation;

  std::vector<io::imp::Base*> vec_importer;
};

}
