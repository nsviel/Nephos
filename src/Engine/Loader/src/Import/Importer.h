#pragma once

#include <Utility/Thread/Thread.h>
#include <string>
#include <vector>

namespace dat::base{class Set;}
namespace dat::base{class Object;}
namespace dat::base{class Set;}
namespace utl::base{class Data;}
namespace utl::base{class Element;}
namespace utl::base{class Path;}
namespace utl::base{class Thread;}
namespace ldr{class Node;}
namespace ldr::importer{class Operation;}
namespace ldr::base{class Importer;}
namespace ldr::base{class Importer;}



namespace ldr::io{

class Importer : public utl::base::Thread
{
public:
  //Constructor / Destructor
  Importer(ldr::Node* node_loader);
  ~Importer();

public:
  //Main functions
  utl::base::Data* load_data(std::string path);
  void load_set(utl::base::Path file_path);
  void load_object(utl::base::Path file_path);

  //Subfunction
  void insert_importer(ldr::base::Importer* importer);
  bool check_path(std::string path);
  bool is_format_supported(std::string format);
  std::vector<std::string> get_supported_format();
  utl::base::Element* import_from_path(utl::base::Path path);

private:
  ldr::importer::Operation* ldr_operation;

  std::vector<ldr::base::Importer*> vec_importer;
};

}
