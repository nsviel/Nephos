#pragma once

#include <Importer/src/Structure/Configuration.h>
#include <Importer/src/Structure/Buffer.h>
#include <Importer/src/Structure/Base.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>

namespace utl::base{class Attribut;}


namespace fmt::pts{

enum Format{
  F0_1 = 0,
  F0_255 = 1,
  F2048_2048 = 2,
};

class Importer : public io::imp::Base
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main function
  utl::base::Element* import(utl::base::Path path);

private:
  //Subfunction
  void retrieve_header(io::imp::Configuration& config);
  void retrieve_size(io::imp::Configuration& config);
  void retrieve_configuration(io::imp::Configuration& confi);
  void retrieve_data(io::imp::Configuration& config);
  void transfer_data(io::imp::Configuration& config, utl::base::Data* data);
  std::vector<float> retrieve_column(io::imp::Configuration& config, int idx);

private:
  utl::base::Attribut* utl_attribut;

  io::imp::Buffer buffer;
  fmt::pts::Format Is_format;
};

}
