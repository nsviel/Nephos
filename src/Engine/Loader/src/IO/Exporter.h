#pragma once

#include <string>
#include <vector>

namespace ldr{class Node;}
namespace utl::base{class Data;}
namespace ldr::base{class Exporter;}


namespace ldr::io{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(ldr::Node* node_loader);
  ~Exporter();

public:
  //Main functions
  void export_data(utl::base::Data* data);

  //Exporter function
  void insert_exporter(ldr::base::Exporter* exporter);
  std::vector<std::string> get_supported_format();

private:
  std::vector<ldr::base::Exporter*> vec_exporter;
};

}
