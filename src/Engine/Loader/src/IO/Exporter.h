#pragma once

#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Format;}
namespace utl::base{class Data;}
namespace ldr::base{class Exporter;}


namespace ldr{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(ldr::Node* node_loader);
  ~Exporter();

public:
  //Main functions
  void export_data(utl::base::Data* data);
  void insert_exporter(ldr::base::Exporter* exporter);

private:
  ldr::Format* ldr_format;

  std::vector<ldr::base::Exporter*> vec_exporter;
};

}
