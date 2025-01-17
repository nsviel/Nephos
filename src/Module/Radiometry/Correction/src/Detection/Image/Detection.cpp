#include "Detection.h"

#include <Radiometry/Correction/Namespace.h>
#include <Data/Namespace.h>
#include <Core/Namespace.h>
#include <Utility/Namespace.h>


namespace rad::cor::image{

//Constructor / Destructor
Detection::Detection(rad::cor::Node* node_correction){
  //---------------------------

  core::Node* node_core = node_correction->get_node_core();
  dat::Node* node_data = node_correction->get_node_data();
  dat::img::Node* node_image = node_data->get_node_image();

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_image = new rad::cor::image::Image(node_correction);
  this->rad_glyph = new rad::cor::Glyph(node_correction);
  this->rad_hough = new rad::cor::image::Hough(node_correction);
  this->thread_pool = node_core->get_thread_pool();
  this->dat_image = node_image->get_dat_image();

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::start_thread(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  if(thread.joinable()){
    this->thread.join();
  }
  this->thread = std::thread(&Detection::run_thread, this, sensor);

  //---------------------------
}
void Detection::run_thread(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  if(rad_struct->state.detection == rad::cor::detection::PROCESSING){
    std::shared_ptr<utl::base::Image> image = dat_image->get_image(*sensor, "Intensity");
    std::shared_ptr<utl::base::Image> output = dat_image->get_or_create_image(*sensor, "Detection");
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
void Detection::make_shape_detection(std::shared_ptr<dat::base::Sensor> sensor, std::shared_ptr<utl::base::Image> image, std::shared_ptr<utl::base::Image> output){
  if(image == nullptr || output == nullptr) return;
  //---------------------------

  cv::Mat cv_image, gray, canny;
  rad_image->convert_into_cv_image(image, cv_image);
  if(cv_image.empty()) return;

  rad_image->convert_into_gray(cv_image, gray);
  rad_image->apply_canny(gray, canny);

  rad_hough->detect_circle(canny, output);
  rad_glyph->draw_detection_sphere(*sensor);

  //---------------------------
}

}
