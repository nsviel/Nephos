#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}
namespace dat::atr{class Field;}


namespace dat::atr{

class Location
{
public:
  // Constructor / Destructor
  Location();
  ~Location();

public:
  //Main function
  void compute_centroid(std::shared_ptr<dat::base::Entity> entity);
  void compute_COM(std::shared_ptr<utl::base::Element> element);
  void compute_COM(std::shared_ptr<dat::base::Set> set);
  void compute_COM(std::shared_ptr<dat::base::Entity> entity);
  void compute_MinMax(std::shared_ptr<dat::base::Set> set);
  void compute_MinMax(std::shared_ptr<dat::base::Entity> entity);
  void compute_height(std::shared_ptr<dat::base::Entity> entity);
  void compute_range(std::shared_ptr<dat::base::Entity> entity);
  void compute_incidence_angle(std::shared_ptr<dat::base::Entity> entity);
  
private:
  dat::atr::Field* atr_field;
};

}
