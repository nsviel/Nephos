#pragma once

#include <highfive/H5File.hpp>
#include <highfive/H5DataSet.hpp>
#include <highfive/H5DataSpace.hpp>

#include <Importer/src/Structure/Base.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>


namespace fmt::hdf5{

class Importer : public io::imp::Base
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main function
  std::shared_ptr<utl::base::Element> import(utl::base::Path path);

private:
  //Subfunction

private:

};

}
