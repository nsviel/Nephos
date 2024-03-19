#include "Model.h"

#include <K4N/Namespace.h>
#include <Operation/Namespace.h>
#include <Scene/Namespace.h>
#include <Engine/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Model::Model(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  eng::scene::Node* node_scene = node_k4n->get_node_scene();

  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_hough = new k4n::calibration::Hough();
  this->ope_fitting = new ope::attribut::Fitting();
  this->sce_glyph = node_scene->get_scene_glyph();
  this->glyph_sphere = new glyph::scene::Sphere(node_engine);

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
    this->draw_glyph_in_cloud(sensor);
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
void Model::draw_glyph_in_cloud(k4n::dev::Sensor* sensor){
  if(vec_circle.size() == 0) return;
  //---------------------------

  uint16_t* buffer = reinterpret_cast<uint16_t*>(sensor->depth.data.buffer);
  int width = sensor->depth.data.width;

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
    xyzw = xyzw * sensor->object.get_pose()->model;


    /*
    utl::file::Path path;
    path.data = glyph_sphere->get_path();
    sce_loader->load_data(path);
    sce_glyph->create_glyph(set_scene, glyph);
    */

    //say(xyzw);
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
