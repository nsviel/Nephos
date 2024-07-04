#pragma once

#include <highfive/H5File.hpp>
//#include <highfive/H5DataSet.hpp>
//#include <highfive/H5DataSpace.hpp>

#include <Loader/src/Base/Importer.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>


namespace format::hdf5{

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

private:

};

}
