#pragma once

#include <Loader/src/Base/Recorder.h>

namespace format::ply{class Exporter;}
namespace utl::base{class Pose;}


namespace format::ply{

class Recorder : public ldr::base::Recorder
{
public:
  //Constructor / Destructor
  Recorder();
  ~Recorder();

public:
  //Main function
  void record_binary(utl::base::Data* data, utl::base::Pose* pose, std::string path);

private:
  format::ply::Exporter* ply_exporter;
};

}
