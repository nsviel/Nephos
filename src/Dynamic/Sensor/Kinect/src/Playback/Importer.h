#pragma once

#include <Importer/src/Structure/Base.h>
#include <string>

namespace k4n{class Node;}
namespace eng{class Node;}
namespace dat::graph{class Graph;}
namespace dat::elm{class Entity;}
namespace dat::elm{class Set;}
namespace dat{class Glyph;}
namespace dyn::element{class Sensor;}


namespace k4n::playback{

class Importer : public io::imp::Base
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
  dat::elm::Entity* dat_entity;
  dat::elm::Set* dat_set;
  dat::Glyph* dat_glyph;
  dyn::element::Sensor* dyn_sensor;
};

}
