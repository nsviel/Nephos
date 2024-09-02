#pragma once

#include <Importer/src/Structure/Base.h>
#include <string>
#include <memory>

namespace io{class Node;}

namespace k4n{class Node;}
namespace k4n{class Utils;}
namespace k4n::playback{class Configuration;}
namespace k4n::playback{class Sensor;}


namespace k4n::playback{

class Importer : public io::imp::Base
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
  k4n::Utils* k4n_utils;
  k4n::playback::Configuration* k4n_config;
};

}
