#pragma once

#include <Loader/src/Base/Importer.h>
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

class Importer : public ldr::base::Importer
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
  void Loader_init();
  void Loader_nbColumns();
  void Loader_configuration();
  void Loader_data(utl::base::Data* data_out, int FILE_config);

  //Checking function
  bool check_header(std::string path);
  int check_configuration(std::string path);
  int check_size(std::string path, bool FILE_hasHeader);

private:
  utl::base::Attribut* utl_attribut;

  std::vector<float> line_columns;
  std::vector<std::string> dataFormat;
  std::string line;
  bool endHeader, FILE_hasHeader;
  bool endParameters;
  bool hasColor;
  bool hasIntensity;
  bool hasNormal;
  int config;
  int nbptMax;
  int FILE_size, FILE_config;
  fmt::pts::IFormat Is_format;
};

}
