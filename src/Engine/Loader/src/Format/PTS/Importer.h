#pragma once

#include <Loader/src/Base/Importer.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>


namespace format::pts{

class Importer : public ldr::base::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main functions
  utl::base::Element* import(utl::media::Path path);

private:
  //Subfunction
  void Loader_init();
  void Loader_nbColumns();
  void Loader_configuration();
  void Loader_data(utl::file::Data* data_out, int FILE_config);

  //Checking function
  bool check_header(std::string path);
  int check_configuration(std::string path);
  int check_size(std::string path, bool FILE_hasHeader);

private:
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
  int IdataFormat;
};

}
