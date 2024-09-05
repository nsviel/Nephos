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

class Loader
{
public:
  //Constructor / Destructor
  Loader(io::imp::Node* node_importer);
  ~Loader();

public:
  //Main function
  std::shared_ptr<utl::base::Data> load_data(std::string path);
  void load_set(utl::base::Path file_path);
  void load_directory(utl::base::Path path);
  void load_object(utl::base::Path file_path);
  void load_object(utl::base::Path file_path, utl::base::Path path_transfo);

  //Subfunction
  void init_path();
  bool check_path(std::string path);

private:
  io::imp::Structure* io_struct;
  io::imp::Operation* io_operation;
};

}
