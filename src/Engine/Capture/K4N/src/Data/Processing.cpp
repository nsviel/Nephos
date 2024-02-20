#include "Processing.h"

#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>
#include <Operation/Namespace.h>
#include <K4N/Namespace.h>


namespace k4n::data{

//Constructor / Destructor
Processing::Processing(){
  //---------------------------

  this->ope_voxelizer = new eng::ope::Voxelizer();
  this->ope_triangulation = new eng::ope::Triangulation();

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

  //Voxelization filtering
  tasker->task_begin("voxel");
  //this->voxelize_object(sensor);
  tasker->task_end("voxel");

  //Triangulation
  tasker->task_begin("triangulation");
  this->triangularize_object(sensor);
  tasker->task_end("triangulation");

  //Update object data
  tasker->task_begin("update");
  this->update_object(sensor);
  tasker->task_end("update");

  tasker->loop_end();

  //---------------------------
}

//Subfunction
void Processing::voxelize_object(k4n::dev::Sensor* sensor){
  //---------------------------

  utl::type::Data* data = sensor->get_data();
  k4n::dev::Master* master = sensor->master;

  float voxel_size = master->voxel.voxel_size;
  int min_nb_point = master->voxel.min_nb_point;
  ope_voxelizer->find_voxel_min_number_of_point(data, voxel_size, min_nb_point);
  ope_voxelizer->reconstruct_data_by_goodness(data);

  //---------------------------
}
void Processing::triangularize_object(k4n::dev::Sensor* sensor){
  //---------------------------

  utl::type::Data* data = sensor->get_data();

  ope_triangulation->make_triangulation(data);

  //---------------------------
}
void Processing::update_object(k4n::dev::Sensor* sensor){
  //---------------------------

  utl::entity::Object* object = sensor->get_object();
  object->update_data();

  //---------------------------
}

}
