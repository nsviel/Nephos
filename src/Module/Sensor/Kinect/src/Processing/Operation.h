#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace dyn{class Structure;}
namespace k4n{class Node;}
namespace k4n::structure{class Sensor;}


namespace k4n::processing{

class Operation
{
public:
  //Constructor / Destructor
  Operation(k4n::Node* node_k4n);
  ~Operation();

public:
  //Data function
  void convert_uint8_to_vec_uint8(const uint8_t* input, size_t size, std::vector<uint8_t>& output);
  void convert_uint8_to_vec_uint16(const uint8_t* input, size_t size, std::vector<uint16_t>& output);

  //IR function
  void find_ir_level(k4n::structure::Sensor* sensor);
  void find_depth_mode_range(k4n::structure::Sensor* sensor);

private:
  dyn::Structure* dyn_struct;
};

}
