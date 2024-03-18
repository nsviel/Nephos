#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::utils{class Hough;}
namespace k4n::calibration{class Model;}
namespace k4n::dev{class Swarm;}
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
  void design_panel();

  //Subfunction
  void model_parameter();
  void hough_parameter();
  void draw_result();

private:
  k4n::utils::Hough* k4n_hough;
  k4n::calibration::Model* k4n_model;
  k4n::dev::Swarm* k4n_swarm;
  eng::render::gui::Stream* stream;

  string name;
  bool* show_window;
};

}
