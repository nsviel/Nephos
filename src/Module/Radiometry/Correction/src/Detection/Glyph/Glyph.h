#pragma once

#include <memory>
#include <vector>

namespace dat::base{class Sensor;}
namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor::structure{class Circle;}
namespace dat::elm{class Glyph;}
namespace dat::elm{class Entity;}
namespace core{class Node;}


namespace rad::cor{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(rad::cor::Node* node_correction);
  ~Glyph();

public:
  //Main function
  void create_sphere_glyph();
  void update_sphere_glyph();

  //Subfunction
  void draw_calibration_sphere(const std::shared_ptr<dat::base::Sensor> sensor);
  void draw_detection_sphere(std::shared_ptr<dat::base::Sensor> sensor);
  void draw_sphere_glyph(std::shared_ptr<dat::base::Sensor> sensor, std::vector<rad::cor::structure::Circle>& vec_circle);

  //Reset function
  void reset_calibration_sphere();
  void reset_detection_sphere();

private:
  core::Node* node_core;
  rad::cor::Structure* rad_struct;
  dat::elm::Glyph* dat_glyph;
  dat::elm::Entity* dat_entity;
};

}
