#include "Model.h"

#include <K4N/Namespace.h>
#include <Operation/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Model::Model(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_hough = new k4n::detection::Hough(node_k4n);
  this->k4n_image = new k4n::matching::Image(node_k4n);
  this->k4n_glyph = new k4n::detection::Glyph(node_k4n);
  this->ope_fitting = new ope::attribut::Fitting();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::determine_model(k4n::dev::Sensor* sensor){
  if(k4n_struct->matching.panel_open == false) return;
  //---------------------------

  this->draw_calibration_image(sensor);
  this->retrieve_sphere_data(sensor);

  //---------------------------
}

//Subfunction
void Model::draw_calibration_image(k4n::dev::Sensor* sensor){
  //---------------------------

  switch(k4n_struct->matching.hough.drawing_mode){
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
void Model::retrieve_sphere_data(k4n::dev::Sensor* sensor){
  //---------------------------

  //Data input
  vector<k4n::structure::Circle>& vec_circle = sensor->detection.vec_circle;
  uint8_t* buffer_ir = sensor->ir.data.buffer;
  uint8_t* buffer_depth = sensor->depth.data.buffer;
  int width = sensor->depth.data.width;

  //Check data
  if(vec_circle.size() == 0) return;

  // Retrieve the parameters of the detected circle
  k4n::structure::Circle& circle = vec_circle[0];
  int x = circle.pose.x;
  int y = circle.pose.y;

  float value_ir = static_cast<float>(buffer_ir[y * width + x]);
  float value_depth = static_cast<float>(buffer_depth[y * width + x]);

  //Convert it into 3D coordinate
  k4a_float2_t source_xy = { static_cast<float>(x), static_cast<float>(y) };
  float source_z = static_cast<float>(buffer_depth[y * width + x]);
  k4a_float3_t target_xyz;
  bool success = sensor->param.calibration.convert_2d_to_3d(source_xy, source_z, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_DEPTH, &target_xyz);
  vec3 xyz = vec3(target_xyz.xyz.x, target_xyz.xyz.y, target_xyz.xyz.z);
  float truc = math::distance_from_origin(xyz);


  //---------------------------
}
void Model::retrieve_bbox_data(k4n::dev::Sensor* sensor){
  //---------------------------

  //Data input
  vector<k4n::structure::Circle>& vec_circle = sensor->detection.vec_circle;
  utl::media::Image* ir = &sensor->image.ir;
  utl::media::Image* depth = &sensor->image.depth;

  //Check data
  if(vec_circle.size() == 0) return;

  //Convert into opencv image
  cv::Mat cv_ir(ir->height, ir->width, CV_8UC4, ir->data.data());
  cv::Mat cv_depth(depth->height, depth->width, CV_8UC4, depth->data.data());

  // Retrieve the parameters of the detected circle
  k4n::structure::Circle& circle = vec_circle[0];
  float center_x = circle.pose.x;
  float center_y = circle.pose.y;
  float radius = circle.radius;

  // Iterate over the bounding box of the circle
  for(int y = center_y - radius; y <= center_y + radius; y++){
    for(int x = center_x - radius; x <= center_x + radius; x++){
      // Calculate the distance from the center of the circle
      float distance = sqrt(pow(x - center_x, 2) + pow(y - center_y, 2));

      // Check if the pixel lies within the circle
      if(distance <= radius){
        // Retrieve the pixel value at (x, y)
        cv::Scalar pixel_value = cv_ir.at<uchar>(y, x);


      }
    }
  }

  //---------------------------
}




}
