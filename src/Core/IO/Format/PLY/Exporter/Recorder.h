#pragma once

#include <Data/Base/Sensor/Recorder.h>

namespace fmt::ply{class Exporter;}
namespace utl::base{class Pose;}


namespace fmt::ply{

class Recorder : public dat::base::sensor::Recorder
{
public:
  //Constructor / Destructor
  Recorder();
  ~Recorder();

public:
  //Main function
  void record_binary(utl::base::Data& data, glm::mat4 mat, std::string path);

private:
  fmt::ply::Exporter* ply_exporter;
};

}
