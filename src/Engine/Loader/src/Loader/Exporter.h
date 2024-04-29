#pragma once

#include <Utility/Specific/Common.h>

namespace sce{class Node;}
namespace ldr{class Format;}


namespace ldr{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(sce::Node* node_scene);
  ~Exporter();

public:
  //Main functions
  void export_data(utl::type::Data* data);

private:
  ldr::Format* sce_format;
};

}
