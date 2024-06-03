#pragma once

#include <string>
#include <vector>

namespace dat::base{class Set;}
namespace dat::base{class Object;}
namespace dat::base{class Set;}
namespace utl::base{class Data;}
namespace utl::base{class Element;}
namespace utl::media{class Path;}
namespace ldr{class Node;}
namespace ldr::processing{class Operation;}
namespace ldr::base{class Importer;}
namespace ldr::base{class Importer;}



namespace ldr::io{

class Importer
{
public:
  //Constructor / Destructor
  Importer(ldr::Node* node_loader);
  ~Importer();

public:
  //Main functions
  utl::base::Data* load_data(std::string path);
  dat::base::Set* load_set(utl::media::Path file_path);
  dat::base::Object* load_object(utl::media::Path file_path);

  //Subfunction
  bool check_path(std::string path);
  utl::base::Element* import_from_path(utl::media::Path path);
  void insert_importer(ldr::base::Importer* importer);
  bool is_format_supported(std::string format);
  std::vector<std::string> get_supported_format();

private:
  ldr::processing::Operation* ldr_operation;
  dat::Graph* dat_graph;
  dat::Set* dat_set;

  std::vector<ldr::base::Importer*> vec_importer;
};

}
