#include "Operation.h"

#include <Utility/Namespace.h>
#include <Operation/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Radiometry/Namespace.h>


namespace dyn::cloud{

//Constructor / Destructor
Operation::Operation(dyn::Node* node_dynamic){
  //---------------------------

  eng::Node* node_engine = node_dynamic->get_node_engine();
  rad::Node* node_radio = node_dynamic->get_node_radio();
  dat::Node* node_data = node_engine->get_node_data();

  this->dat_entity = node_data->get_dat_entity();
  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->ope_voxelizer = new ope::Voxelizer();
  this->ope_trianguler = new ope::Triangulation();
  this->ope_colorizer = new ope::color::Colorizer();
  this->ope_normal = new ope::normal::Structured();
  //this->rad_detection = node_radio->get_cloud_detection();
  this->thread_pool = node_engine->get_thread_pool();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::start_thread(dat::base::Sensor* sensor){
  //---------------------------

  this->thread_idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Operation::run_thread(dat::base::Sensor* sensor){
  //---------------------------

  this->colorize_object(sensor);
  this->normal_object(sensor);
  this->update_object(sensor);

  //---------------------------
  this->thread_idle = true;
}
void Operation::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }


  //---------------------------
}

//Subfunction
void Operation::normal_object(dat::base::Sensor* sensor){
  //---------------------------

  if(dyn_struct->operation.normal.enable){
    ope_normal->set_knn(dyn_struct->operation.normal.knn);
    ope_normal->start_thread(sensor);
    dyn_struct->operation.normal.time = ope_normal->get_time();
  }

  //---------------------------
}
void Operation::colorize_object(dat::base::Entity* entity){
  //---------------------------

  ope::color::Configuration config;
  config.color_mode = dyn_struct->colorization.color_mode;
  config.heatmap_mode = dyn_struct->colorization.heatmap_mode;
  config.intensity_diviser = dyn_struct->colorization.intensity_diviser;
  config.heatmap_range_height = dyn_struct->colorization.range_height;
  config.unicolor = dyn_struct->colorization.unicolor;

  ope_colorizer->make_colorization(entity, config);

  //---------------------------
}
void Operation::voxelize_object(dat::base::Sensor* sensor){
  //---------------------------
/**
  utl::base::Data* data = &sensor->data;
  k4n::dev::Master* master = sensor->master;

  float voxel_size = master->operation.voxel_size;
  int min_nb_point = master->operation.voxel_min_point;
  ope_voxelizer->find_voxel_min_number_of_point(data, voxel_size, min_nb_point);
  ope_voxelizer->reconstruct_data_by_goodness(data);
*/
  //---------------------------
}
void Operation::triangularize_object(dat::base::Sensor* sensor){
  //---------------------------
/*
  utl::base::Data* data = &sensor->data;

  ope_trianguler->make_triangulation(data);
*/
  //---------------------------
}
void Operation::update_object(dat::base::Sensor* sensor){
  //---------------------------

  dat_entity->update_data(sensor);
  //dat_entity->update_glyph(sensor->get_object());

  //---------------------------
}

}
