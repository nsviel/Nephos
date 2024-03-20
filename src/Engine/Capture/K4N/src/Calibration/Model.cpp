#include "Model.h"

#include <K4N/Namespace.h>
#include <Operation/Namespace.h>
#include <Scene/Namespace.h>
#include <Engine/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Model::Model(k4n::Node* node_k4n){
  //---------------------------

  eng::scene::Node* node_scene = node_k4n->get_node_scene();

  this->node_engine = node_k4n->get_node_engine();
  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_hough = new k4n::calibration::Hough();
  this->k4n_image = new k4n::calibration::Image();
  this->ope_fitting = new ope::attribut::Fitting();
  this->sce_glyph = node_scene->get_scene_glyph();

  this->drawing_mode = k4n::hough::ALL;

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::determine_model(k4n::dev::Sensor* sensor){
  //---------------------------

  this->detect_sphere(sensor);
  this->retrieve_sphere_data(sensor);
  this->draw_glyph_in_cloud(sensor);

  //---------------------------
}

//Subfunction
void Model::detect_sphere(k4n::dev::Sensor* sensor){
  //---------------------------

  utl::media::Image* input = &sensor->image.ir;

  sensor->calibration.vec_circle = k4n_hough->sphere_detection(input, sensor->calibration.cv_image);

  switch(drawing_mode){
    case k4n::hough::ALL:{
      k4n_image->draw_all_sphere(sensor);
      break;
    }
    case k4n::hough::BEST:{
      k4n_image->draw_best_sphere(sensor);
      break;
    }
  }

  //---------------------------
}
void Model::draw_glyph_in_cloud(k4n::dev::Sensor* sensor){
  //---------------------------




  uint16_t* buffer = reinterpret_cast<uint16_t*>(sensor->depth.data.buffer);
  int width = sensor->depth.data.width;

  sensor->calibration.vec_sphere_glyph[0]->reset_glyph();

  for(int i=0; i<vec_circle.size(); i++){
    vec3& circle = vec_circle[i];

    // Map depth image pixel to camera space
    int x = circle[0];
    int y = circle[1];
    k4a_float2_t source_xy = { static_cast<float>(x), static_cast<float>(y) };

    int index = y * width + x;
    float source_z = static_cast<float>(buffer[index]);

    // Call the convert_2d_to_3d function
    k4a_float3_t target_xyz;
    bool success = sensor->param.calibration.convert_2d_to_3d(source_xy, source_z, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_DEPTH, &target_xyz);
    vec4 xyzw = vec4(target_xyz.xyz.x, target_xyz.xyz.y, target_xyz.xyz.z, 1);

    //coordinate in meter and X axis oriented.
    float inv_scale = 1.0f / 1000.0f;
    xyzw.x = -xyzw.x * inv_scale;
    xyzw.y = -xyzw.y * inv_scale;
    xyzw.z = xyzw.z * inv_scale;
    xyzw = vec4(xyzw.z, xyzw.x, xyzw.y, 1);
    xyzw = xyzw * sensor->object.get_pose()->model;
    vec3 pose = vec3(xyzw.x, xyzw.y, xyzw.z);

    //Add sphere radius to the detected circle center
    vec3 dir = glm::normalize(pose);
    pose = pose + dir * sphere_diameter;


    sensor->calibration.vec_sphere_glyph[0]->move_sphere(pose);


  }


  //---------------------------
}
void Model::retrieve_sphere_data(k4n::dev::Sensor* sensor){
  if(vec_circle.size() == 0) return;
  //---------------------------

  utl::media::Image* input = &sensor->image.ir;

  cv::Mat cv_image(input->height, input->width, CV_8UC4, input->data.data());

  // Retrieve the parameters of the detected circle
  float center_x = vec_circle[0][0];
  float center_y = vec_circle[0][1];
  float radius = vec_circle[0][2];

  // Iterate over the bounding box of the circle
  for(int y = center_y - radius; y <= center_y + radius; y++){
    for(int x = center_x - radius; x <= center_x + radius; x++){
      // Calculate the distance from the center of the circle
      float distance = sqrt(pow(x - center_x, 2) + pow(y - center_y, 2));

      // Check if the pixel lies within the circle
      if(distance <= radius){
        // Retrieve the pixel value at (x, y)
        cv::Scalar pixel_value = cv_image.at<uchar>(y, x);


      }
    }
  }

  //---------------------------
}




}
