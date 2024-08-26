#pragma once

#include <Exporter/src/Structure/Base.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>


namespace fmt::hdf5{

class Exporter : public io::exp::Base
{
public:
  //Constructor / Destructor
  Exporter();
  ~Exporter();

public:
  //Main funct
  void export_ascii(utl::base::Data& data, glm::mat4 mat, std::string path);

private:
};

}
