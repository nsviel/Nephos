#pragma once

#include <Importer/src/Structure/Base.h>
#include <string>
#include <memory>

namespace k4n{class Node;}
namespace core{class Node;}
namespace dat::gph{class Graph;}
namespace dat::elm{class Entity;}
namespace dat::elm{class Set;}
namespace dat::elm{class Glyph;}
namespace dyn::prc::element{class Sensor;}


namespace k4n::playback{

class Importer : public io::imp::Base
{
public:
  //Constructor / Destructor
  Importer(k4n::Node* node_k4n);
  ~Importer();

public:
  //Main function
  std::shared_ptr<utl::base::Element> import(utl::base::Path path);

  //Subfunction
  float find_mkv_ts_beg(std::string path);
  float find_mkv_ts_end(std::string path);
  std::shared_ptr<dat::base::Set> manage_set_parent();

private:
  k4n::Node* node_k4n;
  core::Node* node_core;
  dat::gph::Graph* dat_graph;
  dat::elm::Entity* dat_entity;
  dat::elm::Set* dat_set;
  dat::elm::Glyph* dat_glyph;
  dyn::prc::element::Sensor* dyn_sensor;
};

}
