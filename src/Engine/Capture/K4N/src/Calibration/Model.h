#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}
namespace k4n::calibration{class Hough;}
namespace ope::attribut{class Fitting;}


namespace k4n::calibration{

class Model
{
public:
  //Constructor / Destructor
  Model(k4n::Node* node_k4n);
  ~Model();

public:
  //Main function
  void determine_model(utl::media::Image* utl_image);

  //Subfunction
  void detect_sphere(utl::media::Image* input, utl::media::Image* gui_image);
  void retrieve_sphere_data(utl::media::Image* utl_image);

  inline float* get_sphere_diameter(){return &sphere_diameter;}
  inline int* get_drawing_mode(){return &drawing_mode;}
  inline k4n::calibration::Hough* get_k4n_hough(){return k4n_hough;}

private:
  k4n::dev::Swarm* k4n_swarm;
  k4n::calibration::Hough* k4n_hough;
  ope::attribut::Fitting* ope_fitting;

  vector<vec3> vec_circle;
  float sphere_diameter = 10;
  int drawing_mode;
};

}
