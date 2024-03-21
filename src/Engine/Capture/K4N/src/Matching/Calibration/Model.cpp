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
  //---------------------------

  this->draw_calibration_image(sensor);
  this->retrieve_sphere_data(sensor);

  //---------------------------
}

//Subfunction
void Model::draw_calibration_image(k4n::dev::Sensor* sensor){
  //---------------------------

  switch(k4n_struct->calibration.hough.drawing_mode){
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

  vector<k4n::structure::Circle>& vec_circle = sensor->detection.vec_circle;
  if(vec_circle.size() == 0) return;

  utl::media::Image* input = &sensor->image.ir;

  cv::Mat cv_image(input->height, input->width, CV_8UC4, input->data.data());

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
        cv::Scalar pixel_value = cv_image.at<uchar>(y, x);


      }
    }
  }

  //---------------------------
}




}
