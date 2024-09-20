#pragma once

#include <memory>
#include <string>
#include <vector>

namespace io::imp{class Node;}
namespace io::imp{class Importer;}
namespace io::imp{class Operation;}
namespace dat::img{class Image;}
namespace utl::base{class Path;}
namespace utl::base{class Data;}
namespace utl::base{class Element;}


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
  void load_object_textured(utl::base::Path path, utl::base::Path path_texture);

  //Subfunction
  bool check_path(utl::base::Path path);
  std::shared_ptr<utl::base::Element> import_from_path(utl::base::Path path);

private:
  io::imp::Importer* io_importer;
  io::imp::Operation* io_operation;
  dat::img::Image* dat_image;
};

}
