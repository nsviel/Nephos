#pragma once

#include <vector>

namespace dyn::base{class Sensor;}
namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction::structure{class Circle;}
namespace dat::elm{class Glyph;}
namespace dat::elm{class Entity;}
namespace eng{class Node;}


namespace rad::correction{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(rad::correction::Node* node_correction);
  ~Glyph();

public:
  //Main function
  void create_sphere_glyph();
  void update_sphere_glyph();

  //Subfunction
  void draw_calibration_sphere(dyn::base::Sensor* sensor);
  void draw_detection_sphere(dyn::base::Sensor* sensor);
  void draw_sphere_glyph(dyn::base::Sensor* sensor, std::vector<rad::correction::structure::Circle>& vec_circle);

  //Reset function
  void reset_calibration_sphere();
  void reset_detection_sphere();

private:
  eng::Node* node_engine;
  rad::correction::Structure* rad_struct;
  dat::elm::Glyph* dat_glyph;
  dat::elm::Entity* dat_entity;
};

}
