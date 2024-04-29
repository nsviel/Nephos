#pragma once

#include <Utility/Specific/Common.h>

namespace sce{class Node;}
namespace sce{class Format;}


namespace sce{

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
  sce::Format* sce_format;
};

}
