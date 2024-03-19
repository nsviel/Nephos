#include "Model.h"

#include <K4N/Namespace.h>
#include <Operation/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Model::Model(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_hough = new k4n::calibration::Hough();
  this->ope_fitting = new ope::attribut::Fitting();

  this->drawing_mode = k4n::hough::ALL;

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::determine_model(utl::media::Image* gui_image){
  k4n::dev::Master* master = k4n_swarm->get_selected_master();
  utl::type::Entity* entity = master->selected_entity;
  //---------------------------

  if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
    utl::media::Image* raw_image = &sensor->image.ir;
    this->detect_sphere(raw_image, gui_image);
    this->retrieve_sphere_data(raw_image);
  }

  //---------------------------
}

//Subfunction
void Model::detect_sphere(utl::media::Image* input, utl::media::Image* gui_image){
  //---------------------------

  this->vec_circle = k4n_hough->sphere_detection(input);

  switch(drawing_mode){
    case k4n::hough::ALL:{
      k4n_hough->draw_all_sphere(input, vec_circle, gui_image);
      break;
    }
    case k4n::hough::BEST:{
      k4n_hough->draw_best_sphere(input, vec_circle, gui_image);
      break;
    }
  }

  //---------------------------
}
void Model::retrieve_sphere_data(utl::media::Image* input){
  if(vec_circle.size() == 0) return;
  //---------------------------

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
