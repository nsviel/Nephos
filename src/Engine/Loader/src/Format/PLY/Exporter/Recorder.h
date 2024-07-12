#pragma once

#include <Dynamic/src/Base/Recorder.h>

namespace fmt::ply{class Exporter;}
namespace utl::base{class Pose;}


namespace fmt::ply{

class Recorder : public dyn::base::Recorder
{
public:
  //Constructor / Destructor
  Recorder();
  ~Recorder();

public:
  //Main function
  void record_binary(utl::base::Data* data, glm::mat4 mat, std::string path);

private:
  fmt::ply::Exporter* ply_exporter;
};

}
