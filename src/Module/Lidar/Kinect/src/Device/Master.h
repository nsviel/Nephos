#pragma once

#include <Data/src/Base/Set.h>
#include <Utility/Specific/Common.h>
#include <Kinect/src/Structure/Namespace.h>
#include <Dynamic/src/Structure/Operation.h>
#include <Dynamic/src/Structure/Recorder.h>

namespace dat{class Set;}
namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::utils{class Configuration;}
namespace dyn::base{class Player;}
namespace dyn::operation{class Structure;}
namespace dyn::recorder{class Structure;}
namespace k4n::structure{class Configuration;}
namespace k4n::playback{class Importer;}
namespace k4n::gui{class Master;}


namespace k4n::dev{

class Master : public dat::base::Set
{
public:
  //Constructor / Destructor
  Master(k4n::Node* node_k4n);
  ~Master();

public:
  //Main function
  void reset();

  //Master function
  void manage_color_control();
  void manage_forward();
  void manage_configuration();

public:
  dat::Set* dat_set;
  k4n::utils::Configuration* k4n_config;
  k4n::playback::Importer* k4n_importer;
  k4n::gui::Master* gui_master;

  dyn::operation::Structure operation;
  dyn::recorder::Structure recorder;
  k4n::structure::Configuration config;
};

}
