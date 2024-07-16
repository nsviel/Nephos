#pragma once

#include <IO/src/Import/Structure/Configuration.h>
#include <IO/src/Import/Structure/Buffer.h>
#include <IO/src/Import/Structure/Base.h>
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

class Importer : public io::importer::Base
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
  void retrieve_header(io::importer::Configuration& config);
  void retrieve_size(io::importer::Configuration& config);
  void retrieve_configuration(io::importer::Configuration& confi);
  void retrieve_data(io::importer::Configuration& config);
  void transfer_data(io::importer::Configuration& config, utl::base::Data* data);
  std::vector<float> retrieve_column(io::importer::Configuration& config, int idx);

private:
  utl::base::Attribut* utl_attribut;

  io::importer::Buffer buffer;
  fmt::pts::Format Is_format;
};

}
