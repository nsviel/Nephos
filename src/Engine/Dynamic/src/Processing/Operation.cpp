#include "Operation.h"

#include <Utility/Namespace.h>
#include <Operation/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Engine/Namespace.h>
#include <Data/Namespace.h>


namespace dyn::processing{

//Constructor / Destructor
Operation::Operation(eng::Node* node_engine){
  //---------------------------

  this->ope_voxelizer = new ope::Voxelizer();
  this->ope_trianguler = new ope::Triangulation();
  this->ope_colorizer = new ope::color::Colorizer();
  this->ope_normal = new ope::normal::KNN();

  this->thread_pool = node_engine->get_thread_pool();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::start_thread(dat::base::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Operation::run_thread(dat::base::Sensor* sensor){
  //---------------------------
/*
  tasker->loop_begin();

  //Colorizer
  this->colorize_object(sensor);


  //Voxelization filtering
  if(master->operation.voxel){
    //this->voxelize_object(sensor);
  }

  //Triangulation
  if(master->operation.triangulation){
    //this->triangularize_object(sensor);
  }

  //Normal
  if(master->operation.normal){
    tasker->task_begin("normal");
    utl::base::Data* data = sensor->get_data();
    // 3 bug :
    // - start segmentation fault
    // - depth to color transformation change
    // - color heatmap (est parfois remplacer par rgb) / normal qui bug time to time
    //ope_normal->compute_normal_with_neighbors(data, sensor->master->operation.normal_knn);
    //k4n_operation->make_normal_from_depth_image(sensor);
    tasker->task_end("normal");
  }*/


  //Update object data
  this->update_object(sensor);

  //---------------------------
  this->idle = true;
}
void Operation::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }


  //---------------------------
}

//Subfunction
void Operation::colorize_object(dat::base::Sensor* sensor){
  //---------------------------
/*
  ope::color::Configuration config;
  config.color_mode = sensor->master->operation.color_mode;
  config.heatmap_mode = sensor->master->operation.heatmap_mode;
  config.intensity_diviser = sensor->master->operation.intensity_diviser;
  config.heatmap_range_height = sensor->master->operation.range_height;
  config.unicolor = sensor->master->operation.unicolor;

  ope_colorizer->make_colorization(sensor, config);
*/
  //---------------------------
}
void Operation::voxelize_object(dat::base::Sensor* sensor){
  //---------------------------
/**
  utl::base::Data* data = sensor->get_data();
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
  utl::base::Data* data = sensor->get_data();

  ope_trianguler->make_triangulation(data);
*/
  //---------------------------
}
void Operation::update_object(dat::base::Sensor* sensor){
  //---------------------------

  sensor->update_data();

  //---------------------------
}

}
