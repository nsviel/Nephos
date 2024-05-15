#include "Data.h"

#include <Kinect/Namespace.h>


namespace k4n::utils{

//Constructor / Destructor
Data::Data(){
  //---------------------------

  //---------------------------
}
Data::~Data(){}

//IR function
void Data::convert_ir_into_color(k4n::dev::Sensor* sensor, std::vector<uint8_t>& output){
  k4n::structure::Data* data = &sensor->ir.data;
  uint8_t* buffer = data->buffer;
  uint16_t level_min = sensor->ir.config.level_min;
  uint16_t level_max = sensor->ir.config.level_max;
  //---------------------------

  output.clear();
  output = std::vector<uint8_t>(data->size * 4, 0);

  for(int i=0, j=0; i<data->size; i+=2, j+=4){
    // Extract the 16-bit infrared value
    float ir = static_cast<uint16_t>(buffer[i]) | (static_cast<uint16_t>(buffer[i + 1]) << 8);

    // Apply intensity division
    ir /= sensor->master->operation.intensity_diviser;
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

  //---------------------------
}
void Data::find_ir_level(k4n::dev::Sensor* sensor){
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
vec3 Data::convert_depth_2d_to_3d(k4n::dev::Sensor* sensor, ivec2 point_2d){
  //---------------------------

  uint16_t* buffer = reinterpret_cast<uint16_t*>(sensor->depth.data.buffer);
  int width = sensor->depth.data.width;

  //Retrieve image coordinates
  int x = point_2d[0];
  int y = point_2d[1];
  k4a_float2_t source_xy = { static_cast<float>(x), static_cast<float>(y) };
  float source_z = static_cast<float>(buffer[y * width + x]);

  //Convert it into 3D coordinate
  k4a_float3_t target_xyz;
  bool success = sensor->device.calibration.convert_2d_to_3d(source_xy, source_z, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_DEPTH, &target_xyz);
  vec4 xyzw = vec4(target_xyz.xyz.x, target_xyz.xyz.y, target_xyz.xyz.z, 1);

  //Apply transformation
  float inv_scale = 1.0f / 1000.0f;
  xyzw.x = -xyzw.x * inv_scale;
  xyzw.y = -xyzw.y * inv_scale;
  xyzw.z = xyzw.z * inv_scale;
  vec3 pose = vec3(xyzw.z, xyzw.x, xyzw.y);

  //---------------------------
  return pose;
}
void Data::convert_depth_into_color(k4n::dev::Sensor* sensor, std::vector<uint8_t>& output){
  k4n::structure::Data* data = &sensor->depth.data;
  uint8_t* inputBuffer = data->buffer;
  uint16_t range_min = sensor->depth.config.range_min;
  uint16_t range_max = sensor->depth.config.range_max;
  //---------------------------

  output.clear();
  output = std::vector<uint8_t>(data->size * 4, 0);

  for(int i=0, j=0; i<data->size; i+=2, j+=4){
    uint16_t r = *reinterpret_cast<const uint16_t*>(&inputBuffer[i]);

    float R = 0.0f;
    float G = 0.0f;
    float B = 0.0f;

    if (r != 0) {
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

  //---------------------------
}
void Data::find_depth_mode_range(k4n::dev::Sensor* sensor){
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
void Data::make_normal_from_depth_image(k4n::dev::Sensor* sensor){
  uint8_t* depth = sensor->depth.data.buffer;
  //---------------------------

  utl::type::Data* data = sensor->get_data();

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

}
