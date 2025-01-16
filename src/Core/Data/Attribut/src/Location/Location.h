#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}
namespace dat::atr::field{class Manager;}


namespace dat::atr{

class Location
{
public:
  // Constructor / Destructor
  Location();
  ~Location();

public:
  //Main function
  void compute_centroid(dat::base::Entity& entity);
  void compute_COM(utl::base::Element& element);
  void compute_COM(dat::base::Set& set);
  void compute_COM(dat::base::Entity& entity);
  void compute_MinMax(dat::base::Set& set);
  void compute_MinMax(dat::base::Entity& entity);
  void compute_height(dat::base::Entity& entity);
  void compute_range(dat::base::Entity& entity);
  void compute_incidence_angle(dat::base::Entity& entity);

private:
  dat::atr::field::Manager* atr_field;
};

}
