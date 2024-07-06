#include "Operation.h"

#include <Kinect/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::processing{

//Constructor / Destructor
Operation::Operation(k4n::Node* node_k4n){
  //---------------------------

  dyn::Node* node_dynamic = node_k4n->get_node_dynamic();

  this->dyn_struct = node_dynamic->get_dyn_struct();

  //---------------------------
}
Operation::~Operation(){}

//Data function
void Operation::convert_uint8_to_vec_uint8(const uint8_t* input, size_t size, std::vector<uint8_t>& output){
  //---------------------------

  output = std::vector<uint8_t>(input, input + size);

  //---------------------------
}
void Operation::convert_uint8_to_vec_uint16(const uint8_t* input, size_t size, std::vector<uint16_t>& output){
  //---------------------------

  // Ensure the input size is even, as each uint16_t is 2 uint8_t
  if(size % 2 != 0){
    throw std::invalid_argument("Input size must be even to convert to uint16_t.");
  }

  // Resize the output vector to hold the correct number of uint16_t values
  size_t outputSize = size / 2;
  output.resize(outputSize);

  // Convert each pair of uint8_t values into a single uint16_t value
  for(size_t i = 0; i < outputSize; ++i){
    output[i] = static_cast<uint16_t>(input[2 * i]) | (static_cast<uint16_t>(input[2 * i + 1]) << 8);
  }

  //---------------------------
}

//IR function
void Operation::find_ir_level(k4n::structure::Sensor* sensor){
  //---------------------------

  if(sensor->depth.config.mode == K4A_DEPTH_MODE_PASSIVE_IR){
    sensor->ir.config.level_min = 0;
    sensor->ir.config.level_max = 100;
  }
  else{
    sensor->depth.config.range_min = 0;
    sensor->depth.config.range_max = 1000;
  }

  //---------------------------
}
void Operation::find_depth_mode_range(k4n::structure::Sensor* sensor){
  //---------------------------

  if(sensor->depth.config.mode == K4A_DEPTH_MODE_NFOV_2X2BINNED){
    sensor->depth.config.range_min = 500;
    sensor->depth.config.range_max = 5800;
  }
  else if(sensor->depth.config.mode == K4A_DEPTH_MODE_NFOV_UNBINNED){
    sensor->depth.config.range_min = 500;
    sensor->depth.config.range_max = 4000;
  }
  else if(sensor->depth.config.mode == K4A_DEPTH_MODE_WFOV_2X2BINNED){
    sensor->depth.config.range_min = 250;
    sensor->depth.config.range_max = 3000;
  }
  else if(sensor->depth.config.mode == K4A_DEPTH_MODE_WFOV_UNBINNED){
    sensor->depth.config.range_min = 250;
    sensor->depth.config.range_max = 2500;
  }

  //---------------------------
}

}
