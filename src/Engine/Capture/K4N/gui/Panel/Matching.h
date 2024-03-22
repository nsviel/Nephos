#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Swarm;}
namespace k4n::dev{class Sensor;}
namespace k4n::structure{class K4N;}
namespace k4n::detection{class Hough;}
namespace k4n::calibration{class Model;}
namespace utl::implot{class Plot;}
namespace eng::render::gui{class Stream;}


namespace k4n::gui{

class Matching
{
public:
  //Constructor / Destructor
  Matching(k4n::Node* node_k4n, bool* show_window);
  ~Matching();

public:
  //Main function
  void run_panel();
  void design_panel(k4n::dev::Master* master);

  //Subfunction
  void model_parameter(k4n::dev::Sensor* sensor);
  void canny_parameter(k4n::dev::Sensor* sensor);
  void hough_parameter(k4n::dev::Sensor* sensor);
  void draw_result(k4n::dev::Sensor* sensor);
  void plot_IfR(k4n::dev::Sensor* sensor);

private:
  k4n::dev::Swarm* k4n_swarm;
  k4n::structure::K4N* k4n_struct;
  k4n::detection::Hough* k4n_hough;
  k4n::calibration::Model* k4n_model;
  utl::implot::Plot* utl_plot;
  eng::render::gui::Stream* stream;

  string name;
  bool* show_window;
};

}
