#pragma once

#include <Utility/Specific/Common.h>

namespace ldr{class Node;}
namespace ldr{class Format;}


namespace ldr{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(ldr::Node* node_scene);
  ~Exporter();

public:
  //Main functions
  void export_data(utl::type::Data* data);

private:
  ldr::Format* ldr_format;
};

}
