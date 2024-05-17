#pragma once

namespace ldr{class Node;}
namespace ldr{class Format;}
namespace utl::base{class Data;}


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

private:
  ldr::Format* ldr_format;
};

}
