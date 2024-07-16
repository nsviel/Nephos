#pragma once

#include <IO/src/Import/Structure/Configuration.h>
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

enum IFormat{
  F0_1 = 0,
  F0_255 = 1,
  FM2048_2048 = 2,
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
  void Loader_nbColumns();
  void Loader_data(utl::base::Data* data_out, int FILE_config);

  //Checking function
  void retrieve_header(io::importer::Configuration& config);
  void retrieve_size(io::importer::Configuration& config);
  void retrieve_configuration(io::importer::Configuration& confi);
  std::vector<float> retrieve_column(io::importer::Configuration& config, int idx);

private:
  utl::base::Attribut* utl_attribut;

  std::vector<float> line_columns;
  std::vector<std::string> dataFormat;
  std::string line;

  bool hasColor;
  bool hasIntensity;
  bool hasNormal;
  fmt::pts::IFormat Is_format;
};

}
