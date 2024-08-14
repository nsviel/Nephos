#include "Converter.h"

#include <Transformation/Namespace.h>
#include <Data/Namespace.h>
#include <opencv2/opencv.hpp>


namespace ope::image{

//Constructor / Destructor
Converter::Converter(){
  //---------------------------

  this->utl_attribut = new utl::base::Attribut();

  //---------------------------
}
Converter::~Converter(){}

//Main function
void Converter::convert_normal_to_image(utl::base::Data* data, utl::media::Image* image){
  if(data == nullptr) return;
  //---------------------------

  std::vector<glm::vec3>& Nxyz = data->Nxyz;
  if(Nxyz.size() == 0) return;

  std::vector<uint8_t> output = std::vector<uint8_t>(Nxyz.size() * 4, 0);

  // Convert the float value to uint8_t
  for(int i=0; i<Nxyz.size(); i++){
    glm::vec3 normal = Nxyz[i];

    size_t j = i * 4;
    if(normal != glm::vec3(0, 0, 0)){
      output[j]     = (1 + normal.x) / 2 * 255.0f;
      output[j + 1] = (1 + normal.y) / 2 * 255.0f;
      output[j + 2] = (1 + normal.z) / 2 * 255.0f;
      output[j + 3] = 255.0f;
    }else{
      output[j]     = 0.0f;
      output[j + 1] = 0.0f;
      output[j + 2] = 0.0f;
      output[j + 3] = 255.0f;
    }
  }

  //Update image
  image->size = output.size();
  image->width = data->width;
  image->height = data->height;
  image->data = output;
  image->name = "Normal";

  //---------------------------
}
void Converter::convert_intensity_to_image(utl::base::Data* data, utl::media::Image* image){
  if(data == nullptr) return;
  //---------------------------

  std::vector<float>& vec_I = utl_attribut->get_field_data(data, "I");
  std::vector<uint8_t> output = std::vector<uint8_t>(vec_I.size() * 4, 0);

  // Convert the float value to uint8_t
  for(int i=0; i<vec_I.size(); i++){
    float intensity = vec_I[i];

    size_t j = i * 4;
    output[j]     = intensity * 255.0f;
    output[j + 1] = intensity * 255.0f;
    output[j + 2] = intensity * 255.0f;
    output[j + 3] = 255.0f;
  }

  //Update image
  image->size = output.size();
  image->width = data->width == -1 ? 200 : data->width;
  image->height = data->height == -1 ? 100 : data->height;
  image->data = output;

  //---------------------------
}
void Converter::convert_spherical_pc_to_image(utl::base::Data* data, utl::media::Image* image){
  if(data == nullptr) return;
  //---------------------------

  std::vector<float>& vec_I = utl_attribut->get_field_data(data, "I");
  std::vector<glm::vec3>& vec_xyz = data->xyz;
  int width = 10000;
  int height = 5000;
  int num_images = 4;
  float segment_angle = 2 * M_PI / num_images;

  // Create empty intensity images for each segment
  std::vector<cv::Mat> vec_images(num_images, cv::Mat::zeros(height, width, CV_32FC1));

  // Loop over each point in the point cloud
  for(int i = 0; i < vec_xyz.size(); i++) {
     glm::vec3& xyz = vec_xyz[i];
     float& Is = vec_I[i];

     // Convert Cartesian coordinates to spherical coordinates
     float radius = std::sqrt(xyz.x * xyz.x + xyz.y * xyz.y + xyz.z * xyz.z);
     float azimuth = std::atan2(xyz.y, xyz.x); // Horizontal angle
     float elevation = std::asin(xyz.z / radius); // Vertical angle

     // Determine which segment the point belongs to
     int segment_index = static_cast<int>((azimuth + M_PI) / segment_angle) % num_images;

     // Map azimuth and elevation to pixel coordinates
     float local_azimuth = azimuth - (segment_index * segment_angle - M_PI);
     int u = static_cast<int>((local_azimuth + segment_angle / 2) / segment_angle * width); // azimuth: [segment_start, segment_end] -> [0, width]
     int v = static_cast<int>((M_PI / 2 - elevation) / M_PI * height); // elevation: [-pi/2, pi/2] -> [0, height]

     // Ensure the coordinates are within image bounds
     u = std::clamp(u, 0, width - 1);
     v = std::clamp(v, 0, height - 1);

     // Set the intensity value
     vec_images[segment_index].at<float>(v, u) = Is;
  }

  // Normalize and save each image
  for (int i = 0; i < num_images; i++) {
     cv::normalize(vec_images[i], vec_images[i], 0, 1, cv::NORM_MINMAX);
     cv::Mat cv_image_8u;
     vec_images[i].convertTo(cv_image_8u, CV_8UC1, 255.0);
     std::string output_path = std::string(getenv("HOME")) + "/Desktop/intensity_image_" + std::to_string(i) + ".png";
     cv::imwrite(output_path, cv_image_8u);
  }

  //---------------------------
}
void Converter::convert_whole_spherical_pc_to_image(utl::base::Data* data, utl::media::Image* image){
  if(data == nullptr) return;
  //---------------------------

  std::vector<float>& vec_I = utl_attribut->get_field_data(data, "I");
  std::vector<glm::vec3>& vec_xyz = data->xyz;
  int width = 20000;
  int height = 10000;

  // Create an empty intensity image
  cv::Mat cv_image = cv::Mat::zeros(height, width, CV_32FC1);

  // Loop over each point in the point cloud
  for(int i=0; i<vec_xyz.size(); i++){
    glm::vec3& xyz = vec_xyz[i];
    float& Is = vec_I[i];

    // Convert Cartesian coordinates to spherical coordinates
    float radius = std::sqrt(xyz.x * xyz.x + xyz.y * xyz.y + xyz.z * xyz.z);
    float azimuth = std::atan2(xyz.y, xyz.x); // Horizontal angle
    float elevation = std::asin(xyz.z / radius); // Vertical angle

    // Map azimuth and elevation to pixel coordinates
    int u = static_cast<int>((azimuth + M_PI) / (2 * M_PI) * width); // azimuth: [-pi, pi] -> [0, width]
    int v = static_cast<int>((M_PI / 2 - elevation) / M_PI * height); // elevation: [-pi/2, pi/2] -> [0, height]

    // Ensure the coordinates are within image bounds
    u = std::clamp(u, 0, width - 1);
    v = std::clamp(v, 0, height - 1);

    // Set the intensity value
    cv_image.at<float>(v, u) = Is;
  }

  // Normalize the intensity image to the range [0, 1]
  cv::normalize(cv_image, cv_image, 0, 1, cv::NORM_MINMAX);

  // Convert the intensity image to CV_8UC1
  cv::Mat cv_image_8u;
  cv_image.convertTo(cv_image_8u, CV_8UC1, 255.0);

  std::string output_path = std::string(getenv("HOME")) + "/Desktop/intensity_image.png";
  cv::imwrite(output_path, cv_image_8u);

  // Flatten the matrix and copy its data to a vector
  std::vector<uint8_t> output(cv_image_8u.total());
  std::memcpy(output.data(), cv_image_8u.data, output.size() * sizeof(uint8_t));

  //Update image
  image->size = output.size();
  image->width = width;
  image->height = height;
  image->data = output;

  //---------------------------
}
void Converter::convert_color_to_image(utl::base::Data* data, utl::media::Image* image){
  if(data == nullptr) return;
  //---------------------------

  std::vector<uint8_t> output = std::vector<uint8_t>(data->rgb.size() * 4, 0);

  // Convert the float value to uint8_t
  for(int i=0; i<data->rgb.size(); i++){
    glm::vec3& rgb = data->rgb[i];

    size_t j = i * 4;
    output[j]     = rgb.x * 255.0f;
    output[j + 1] = rgb.y * 255.0f;
    output[j + 2] = rgb.z * 255.0f;
    output[j + 3] = 255.0f;
  }

  //Update image
  image->size = output.size();
  image->width = data->width;
  image->height = data->height;
  image->data = output;

  //---------------------------
}

}
