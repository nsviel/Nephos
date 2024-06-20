#include "Data.h"

#include <Kinect/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::utils{

//Constructor / Destructor
Data::Data(k4n::Node* node_k4n){
  //---------------------------

  dyn::Node* node_dynamic = node_k4n->get_node_dynamic();

  this->dyn_struct = node_dynamic->get_dyn_struct();

  //---------------------------
}
Data::~Data(){}

//Data function
void Data::convert_uint8_to_vec_uint8(const uint8_t* input, size_t size, std::vector<uint8_t>& output){
  //---------------------------

  output = std::vector<uint8_t>(input, input + size);

  //---------------------------
}
void Data::convert_uint8_to_vec_uint16(const uint8_t* input, size_t size, std::vector<uint16_t>& output){
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
void Data::convert_ir_into_color(k4n::structure::Sensor* sensor){
  k4n::structure::Data* data = &sensor->ir.data;
  uint8_t* buffer = data->buffer;
  uint16_t level_min = sensor->ir.config.level_min;
  uint16_t level_max = sensor->ir.config.level_max;
  //---------------------------

  std::vector<uint8_t> output = std::vector<uint8_t>(data->size * 4, 0);

  for(int i=0, j=0; i<data->size; i+=2, j+=4){
    // Extract the 16-bit infrared value
    float ir = static_cast<uint16_t>(buffer[i]) | (static_cast<uint16_t>(buffer[i + 1]) << 8);

    // Apply intensity division
    ir /= dyn_struct->operation.intensity.diviser;
    if(ir < 0) ir = 0;
    if(ir > 1) ir = 1;

    // Convert the float value to uint8_t
    uint8_t value = static_cast<uint8_t>(ir * 255.0f);

    // Assign the value to the output vector for each channel (R, G, B, Alpha)
    output[j] = value;
    output[j + 1] = value;
    output[j + 2] = value;
    output[j + 3] = 255;
  }

  sensor->ir.image.data = output;

  //---------------------------
}
void Data::find_ir_level(k4n::structure::Sensor* sensor){
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

//Depth function
void Data::convert_depth_into_color(k4n::structure::Sensor* sensor){
  k4n::structure::Data* data = &sensor->depth.data;
  uint8_t* inputBuffer = data->buffer;
  uint16_t range_min = sensor->depth.config.range_min;
  uint16_t range_max = sensor->depth.config.range_max;
  //---------------------------

  std::vector<uint8_t> output = std::vector<uint8_t>(data->size * 4, 0);

  for(int i=0, j=0; i<data->size; i+=2, j+=4){
    uint16_t r = *reinterpret_cast<const uint16_t*>(&inputBuffer[i]);

    float R = 0.0f;
    float G = 0.0f;
    float B = 0.0f;

    if(r != 0){
      uint16_t clamped = r;
      clamped = std::min(clamped, range_max);
      clamped = std::max(clamped, range_min);
      float hue = (clamped - range_min) / static_cast<float>(range_max - range_min);
      constexpr float range = 2.f / 3.f;
      hue *= range;
      hue = range - hue;

      ImGui::ColorConvertHSVtoRGB(hue, 1.f, 1.f, R, G, B);
    }

    output[j] = static_cast<uint8_t>(R * 255);
    output[j + 1] = static_cast<uint8_t>(G * 255);
    output[j + 2] = static_cast<uint8_t>(B * 255);
    output[j + 3] = 255;
  }

  sensor->depth.image.data = output;

  //---------------------------
}
void Data::find_depth_mode_range(k4n::structure::Sensor* sensor){
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

//Normal function
void Data::make_normal_from_depth_image(k4n::structure::Sensor* sensor){
  uint8_t* depth = sensor->depth.data.buffer;
  //---------------------------

  utl::base::Data* data = &sensor->data;

  int width = sensor->depth.data.width;
  int height = sensor->depth.data.height;
  vector<vec3> Nxyz;

 //BUT OBTENIR UNE NORMAL IMAGE FROM DEPTH IMAGE

  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){

      int id_1 = i * width + j + 1;
      int id_2 = i * width + j - 1;
      uint16_t value_1 = depth[id_1 * 2] | (depth[id_1 * 2 + 1] << 8);
      uint16_t value_2 = depth[id_2 * 2] | (depth[id_2 * 2 + 1] << 8);
      float dzdx = (value_1 - value_2) / 2.0;

      id_1 = (i + 1) * width + j;
      id_2 = (i - 1) * width + j;
      value_1 = depth[id_1 * 2] | (depth[id_1 * 2 + 1] << 8);
      value_2 = depth[id_2 * 2] | (depth[id_2 * 2 + 1] << 8);
      float dzdy = (value_1 - value_2) / 2.0;

      vec3 d(-dzdx, -dzdy, 1.0f);
      vec3 n = glm::normalize(d);

      Nxyz.push_back(n);
    }
  }

data->Nxyz = Nxyz;

/*
  for(int x = 0; x < depth.rows; ++x)
  {
      for(int y = 0; y < depth.cols; ++y)
      {

          float dzdx = (depth.at<float>(x+1, y) - depth.at<float>(x-1, y)) / 2.0;
          float dzdy = (depth.at<float>(x, y+1) - depth.at<float>(x, y-1)) / 2.0;

          Vec3f d(-dzdx, -dzdy, 1.0f);
          Vec3f n = normalize(d);

          normals.at<Vec3f>(x, y) = n;
      }
  }

  imshow("depth", depth / 255);
  imshow("normals", normals);
*/
  //---------------------------
}
void Data::convert_normal_into_color(k4n::structure::Sensor* sensor, std::vector<glm::vec3>& vec_Nxyz){
  //---------------------------

  std::vector<uint8_t> output = std::vector<uint8_t>(vec_Nxyz.size() * 4, 0);

  // Convert the float value to uint8_t
  for(int i=0; i<vec_Nxyz.size(); i++){
    glm::vec3 normal = vec_Nxyz[i];

    size_t j = i * 4;
    output[j] = normal.x * 255.0f;
    output[j + 1] = normal.y * 255.0f;
    output[j + 2] = normal.z * 255.0f;
    output[j + 3] = 255;
  }

  //sensor->normal.image.data = output;

  //---------------------------
}

}
