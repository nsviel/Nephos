#include "Processing.h"

#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>
#include <Operation/Namespace.h>
#include <K4N/Namespace.h>


namespace k4n::data{

//Constructor / Destructor
Processing::Processing(){
  //---------------------------

  this->ope_voxelizer = new ope::Voxelizer();
  this->ope_trianguler = new ope::Triangulation();
  this->ope_colorizer = new ope::color::Colorizer();
  this->ope_normal = new ope::attribut::Normal();
  this->k4n_operation = new k4n::utils::Operation();

  //---------------------------
}
Processing::~Processing(){}

//Main function
void Processing::start_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  if(thread.joinable()){
    thread.join();
  }
  this->thread = std::thread(&Processing::run_thread, this, sensor);

  //---------------------------
}
void Processing::run_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  prf::Tasker* tasker = sensor->profiler->get_tasker("processing");
  tasker->loop_begin();

  //Colorizer
  tasker->task_begin("colorization");
  this->colorize_object(sensor);
  tasker->task_end("colorization");

  //Voxelization filtering
  tasker->task_begin("voxel");
  //this->voxelize_object(sensor);
  tasker->task_end("voxel");

  //Triangulation
  tasker->task_begin("triangulation");
  //this->triangularize_object(sensor);
  tasker->task_end("triangulation");

  //Triangulation
  tasker->task_begin("normal");
  utl::type::Data* data = sensor->get_data();
  ope_normal->compute_normal_with_neighbors(data, sensor->master->operation.normal_knn);
  //k4n_operation->compute_normal_from_depth_image(sensor);
  tasker->task_end("normal");

  //Update object data
  tasker->task_begin("update");
  this->update_object(sensor);
  tasker->task_end("update");

  tasker->loop_end();

  //---------------------------
}

//Subfunction
void Processing::colorize_object(k4n::dev::Sensor* sensor){
  //---------------------------

  ope::color::Configuration config;
  config.color_mode = sensor->master->operation.color_mode;
  config.heatmap_mode = sensor->master->operation.heatmap_mode;
  config.intensity_division = sensor->master->operation.intensity_division;
  config.heatmap_range_height = sensor->master->operation.range_height;
  config.unicolor = sensor->master->operation.unicolor;

  ope_colorizer->make_colorization(sensor, config);

  //---------------------------
}
void Processing::voxelize_object(k4n::dev::Sensor* sensor){
  //---------------------------

  utl::type::Data* data = sensor->get_data();
  k4n::dev::Master* master = sensor->master;

  float voxel_size = master->operation.voxel_size;
  int min_nb_point = master->operation.voxel_min_point;
  ope_voxelizer->find_voxel_min_number_of_point(data, voxel_size, min_nb_point);
  ope_voxelizer->reconstruct_data_by_goodness(data);

  //---------------------------
}
void Processing::triangularize_object(k4n::dev::Sensor* sensor){
  //---------------------------

  utl::type::Data* data = sensor->get_data();

  ope_trianguler->make_triangulation(data);

  //---------------------------
}
void Processing::update_object(k4n::dev::Sensor* sensor){
  //---------------------------

  utl::entity::Object* object = sensor->get_object();
  object->update_data();
  object->update_glyph();

  //---------------------------
}

}
