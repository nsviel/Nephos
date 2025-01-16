#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <string>

namespace dat::atr::field{class Manager;}
namespace utl::base{class Data;}
namespace utl::base{class Field;}


namespace dat::atr::field{

class Operation
{
public:
  Operation();
  ~Operation();

public:
  //Main function
  void normalize_field(utl::base::Data& data, const std::string& name);

private:
  dat::atr::field::Manager* atr_field;
};

}
