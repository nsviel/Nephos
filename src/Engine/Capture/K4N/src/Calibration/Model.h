#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}
namespace k4n::dev{class Sensor;}
namespace k4n::calibration{class Hough;}
namespace ope::attribut{class Fitting;}
namespace eng::scene{class Glyph;}
namespace eng{class Node;}
namespace glyph::scene{class Sphere;}


namespace k4n::calibration{

class Model
{
public:
  //Constructor / Destructor
  Model(k4n::Node* node_k4n);
  ~Model();

public:
  //Main function
  void init();
  void determine_model(utl::media::Image* utl_image);

  //Subfunction
  void detect_sphere(utl::media::Image* input, utl::media::Image* gui_image);
  void draw_glyph_in_cloud(k4n::dev::Sensor* sensor);
  void retrieve_sphere_data(utl::media::Image* utl_image);

  inline float* get_sphere_diameter(){return &sphere_diameter;}
  inline int* get_drawing_mode(){return &drawing_mode;}
  inline k4n::calibration::Hough* get_k4n_hough(){return k4n_hough;}

private:
  eng::Node* node_engine;
  k4n::dev::Swarm* k4n_swarm;
  k4n::calibration::Hough* k4n_hough;
  ope::attribut::Fitting* ope_fitting;
  eng::scene::Glyph* sce_glyph;

  vector<glyph::scene::Sphere*> vec_sphere;
  vector<vec3> vec_circle;
  float sphere_diameter = 0.1;
  int drawing_mode;
};

}
