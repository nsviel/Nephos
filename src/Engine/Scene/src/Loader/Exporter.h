#pragma once

#include <Utility/Specific/Common.h>

namespace eng::scene{class Node;}
namespace eng::scene{class Format;}


namespace eng::scene{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(eng::scene::Node* node_scene);
  ~Exporter();

public:
  //Main functions
  void export_data(utl::type::Data* data);

private:
  eng::scene::Format* sce_format;
};

}
