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
  utl::media::File* import(utl::media::Path path);
  utl::media::File* import(utl::media::Path path, int lmin, int lmax);

  inline void set_IdataFormat(int value){this->IdataFormat = value;}
  inline void set_retrievingIntensity(bool value){this->retrieve_I = value;}
  inline void set_retrievingColor(bool value){this->retrieve_rgb = value;}
  inline void set_retrievingNormal(bool value){this->retrieve_N = value;}

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
  bool retrieve_I, retrieve_rgb, retrieve_N;
  int config;
  int nbptMax;
  int FILE_size, FILE_config;
  int IdataFormat, export_IdataFormat;
};

}
