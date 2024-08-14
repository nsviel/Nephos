#pragma once

#include <IO/src/Import/Structure/Base.h>
#include <string>

namespace k4n{class Node;}
namespace eng{class Node;}
namespace dat::graph{class Graph;}
namespace dat::element{class Entity;}
namespace dat::element{class Set;}
namespace dat{class Glyph;}
namespace dyn::element{class Sensor;}


namespace k4n::playback{

class Importer : public io::importer::Base
{
public:
  //Constructor / Destructor
  Importer(k4n::Node* node_k4n);
  ~Importer();

public:
  //Main function
  utl::base::Element* import(utl::base::Path path);

  //Subfunction
  float find_mkv_ts_beg(std::string path);
  float find_mkv_ts_end(std::string path);
  dat::base::Set* manage_set_parent();

private:
  k4n::Node* node_k4n;
  eng::Node* node_engine;
  dat::graph::Graph* dat_graph;
  dat::element::Entity* dat_entity;
  dat::element::Set* dat_set;
  dat::Glyph* dat_glyph;
  dyn::element::Sensor* dyn_sensor;
};

}