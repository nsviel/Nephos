#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Swarm;}
namespace k4n::dev{class Sensor;}
namespace k4n::calibration{class Hough;}
namespace k4n::calibration{class Model;}
namespace eng::render::gui{class Stream;}


namespace k4n::gui{

class Calibration
{
public:
  //Constructor / Destructor
  Calibration(k4n::Node* node_k4n, bool* show_window);
  ~Calibration();

public:
  //Main function
  void run_panel();
  void design_panel(k4n::dev::Master* master);

  //Subfunction
  void model_parameter(k4n::dev::Sensor* sensor);
  void hough_parameter(k4n::dev::Sensor* sensor);
  void draw_result(k4n::dev::Sensor* sensor);

private:
  k4n::dev::Swarm* k4n_swarm;
  k4n::calibration::Hough* k4n_hough;
  k4n::calibration::Model* k4n_model;
  eng::render::gui::Stream* stream;

  string name;
  bool* show_window;
};

}
