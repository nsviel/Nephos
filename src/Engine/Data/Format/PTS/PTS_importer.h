#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Base/Struct_file.h>
#include <Engine/Base/Namespace.h>
#include <Utility/Function/File/Info.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>


class PTS_importer
{
public:
  //Constructor / Destructor
  PTS_importer();
  ~PTS_importer();

public:
  //Main functions
  utility::base::File* Loader(std::string pathFile);
  utility::base::File* Loader(std::string pathFile, int lmin, int lmax);

  bool Exporter(std::string pathFile, eng::structure::Object* object);

  inline void set_IdataFormat(int value){this->IdataFormat = value;}
  inline void set_retrievingIntensity(bool value){this->retrieve_I = value;}
  inline void set_retrievingColor(bool value){this->retrieve_RGB = value;}
  inline void set_retrievingNormal(bool value){this->retrieve_N = value;}

private:
  //Subfunctions
  void Loader_init();
  void Loader_nbColumns();
  void Loader_configuration();
  void Loader_data(utility::base::File* data_out, int FILE_config);

  //Loader sub-functions
  bool check_header(std::string pathFile);
  int check_configuration(std::string pathFile);
  int check_size(std::string pathFile, bool FILE_hasHeader);

private:
  std::vector<float> line_columns;
  std::vector<std::string> dataFormat;
  std::string line;
  bool endHeader, FILE_hasHeader;
  bool endParameters;
  bool hasColor;
  bool hasIntensity;
  bool hasNormal;
  bool retrieve_I, retrieve_RGB, retrieve_N;
  int config;
  int nbptMax;
  int FILE_size, FILE_config;
  int IdataFormat, export_IdataFormat;

};
