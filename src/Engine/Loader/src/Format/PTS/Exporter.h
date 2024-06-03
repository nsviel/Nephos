#pragma once

#include <Loader/src/Base/Exporter.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>


namespace format::pts{

class Exporter : public ldr::base::Exporter
{
public:
  //Constructor / Destructor
  Exporter();
  ~Exporter();

public:
  //Main funct
  void export_ascii(utl::base::Data* data, utl::base::Pose* pose, std::string path);

private:
};

}