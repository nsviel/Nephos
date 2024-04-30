#pragma once

namespace ldr{class Node;}
namespace ldr{class Format;}
namespace utl::type{class Data;}


namespace ldr{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(ldr::Node* node_loader);
  ~Exporter();

public:
  //Main functions
  void export_data(utl::type::Data* data);

private:
  ldr::Format* ldr_format;
};

}
