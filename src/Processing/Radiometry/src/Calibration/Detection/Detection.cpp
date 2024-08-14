#include "Detection.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Core/Namespace.h>


namespace rad::calibration{

//Constructor / Destructor
Detection::Detection(rad::calibration::Node* node_detection){
  //---------------------------

  rad::Node* node_radio = node_detection->get_node_radio();
  eng::Node* node_engine = node_radio->get_node_engine();
  dat::Node* node_data = node_radio->get_node_data();

  this->rad_struct = node_detection->get_rad_struct();
  this->rad_image = new rad::calibration::Image(node_detection);
  this->rad_rectangle = new rad::calibration::Rectangle(node_detection);
  this->thread_pool = node_engine->get_thread_pool();
  this->dat_image = node_data->get_dat_image();

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::start_thread(dyn::base::Sensor* sensor){
  //---------------------------

  this->thread_idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Detection::run_thread(dyn::base::Sensor* sensor){
  //---------------------------

  if(sensor != nullptr){// && rad_struct->state.detection == rad::calibration::detection::PROCESSING){
    utl::media::Image* image = dat_image->get_image(sensor, "Intensity");
    utl::media::Image* output = dat_image->get_or_create_image(sensor, "Detection");
    if(image == nullptr || output == nullptr) return;

    if(image->timestamp != output->timestamp){
      output->name = "Detection";
      output->timestamp = image->timestamp;
      this->make_shape_detection(sensor, image, output);
    }
  }

  //---------------------------
  this->thread_idle = true;
}
void Detection::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Detection::make_shape_detection(dyn::base::Sensor* sensor, utl::media::Image* image, utl::media::Image* output){
  //---------------------------

  cv::Mat cv_image, gray, canny;
  rad_image->convert_into_cv_image(image, cv_image);
  rad_image->convert_into_gray(cv_image, gray);


  // Make binary image
  cv::Mat bw;
  cv::threshold(gray, bw, 254, 255, cv::THRESH_BINARY);

  // Focus on edges
  cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
  cv::erode(bw, bw, kernel);

  // Step 2: Flood fill to remove noise
  cv::floodFill(bw, cv::Point(0, 0), 0);

  // Step 3: Median blur
  cv::medianBlur(bw, bw, 7);

  // Step 4: Second flood fill
  cv::Mat nonRectArea = bw.clone();  // Create a copy for nonRectArea
  cv::floodFill(nonRectArea, cv::Point(cv_image.cols/2, cv_image.rows/2), 0);

  // Remove remained noise
  bw.setTo(0, nonRectArea == 255);



  rad_image->apply_canny(nonRectArea, canny);

  rad_rectangle->detect_rectangle(canny, output);

  //---------------------------
}

}
