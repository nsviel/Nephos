#pragma once

#include <Utility/Specific/Common.h>

namespace scene{class Node;}
namespace scene{class Format;}


namespace scene{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(scene::Node* node_scene);
  ~Exporter();

public:
  //Main functions
  void export_data(utl::type::Data* data);

private:
  scene::Format* sce_format;
};

}
