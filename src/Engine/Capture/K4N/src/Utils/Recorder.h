#pragma once

#include <Utility/Specific/common.h>

namespace k4n::structure{class Struct_k4n;}
namespace eng::scene{class Loader;}


namespace k4n::utils{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(k4n::structure::Struct_k4n* struct_k4n);
  ~Recorder();

public:
  //Main function
  void make_cloud_export(k4n::dev::Sensor* sensor);

private:
  k4n::structure::Struct_k4n* struct_k4n;
  eng::scene::Loader* sce_loader;
};

}
