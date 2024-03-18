#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}
namespace k4n::utils{class Hough;}
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
  void detect_sphere(utl::media::Image* utl_image);

  inline float* get_sphere_diameter(){return &sphere_diameter;}
  inline k4n::utils::Hough* get_k4n_hough(){return k4n_hough;}

private:
  k4n::dev::Swarm* k4n_swarm;
  k4n::utils::Hough* k4n_hough;
  ope::attribut::Fitting* ope_fitting;

  float sphere_diameter = 10;
};

}
