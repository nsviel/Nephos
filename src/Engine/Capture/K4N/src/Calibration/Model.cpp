#include "Model.h"

#include <K4N/Namespace.h>
#include <Operation/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Model::Model(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_hough = new k4n::calibration::Hough(node_k4n);
  this->k4n_image = new k4n::calibration::Image(node_k4n);
  this->k4n_glyph = new k4n::calibration::Glyph(node_k4n);
  this->ope_fitting = new ope::attribut::Fitting();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::determine_model(k4n::dev::Sensor* sensor){
  //---------------------------

  this->detect_sphere(sensor);
  this->retrieve_sphere_data(sensor);
  k4n_glyph->draw_glyph(sensor);

  //---------------------------
}

//Subfunction
void Model::detect_sphere(k4n::dev::Sensor* sensor){
  //---------------------------

  utl::media::Image* input = &sensor->image.ir;
  cv::Mat cv_input;
  k4n_image->convert_into_cv_image(input, cv_input);
  sensor->calibration.vec_circle = k4n_hough->sphere_detection(cv_input, sensor->calibration.cv_image);
  sensor->calibration.nb_detection = sensor->calibration.vec_circle.size();

  switch(k4n_struct->hough.drawing_mode){
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
  if(sensor->calibration.vec_circle.size() == 0) return;
  //---------------------------

  utl::media::Image* input = &sensor->image.ir;

  cv::Mat cv_image(input->height, input->width, CV_8UC4, input->data.data());

  // Retrieve the parameters of the detected circle
  float center_x = sensor->calibration.vec_circle[0][0];
  float center_y = sensor->calibration.vec_circle[0][1];
  float radius = sensor->calibration.vec_circle[0][2];

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
