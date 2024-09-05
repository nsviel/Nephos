#pragma once

#include <Importer/src/Base/Importer.h>
#include <string>
#include <memory>

namespace io{class Node;}

namespace k4n{class Node;}
namespace k4n{class Factory;}
namespace k4n::playback{class Configuration;}
namespace k4n::playback{class Sensor;}


namespace k4n::playback{

class Importer : public io::base::Importer
{
public:
  //Constructor / Destructor
  Importer(k4n::Node* node_k4n);
  ~Importer();

public:
  //Main function
  void insert_importer();

  //Subfunction
  std::shared_ptr<utl::base::Element> import(utl::base::Path path);

private:
  io::Node* node_io;

  k4n::Node* node_k4n;
  k4n::Factory* k4n_factory;
  k4n::playback::Configuration* k4n_config;
};

}
