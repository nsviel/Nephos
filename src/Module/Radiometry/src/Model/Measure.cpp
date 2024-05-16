#include "Measure.h"

#include <Kinect/Namespace.h>
#include <Radiometry/Namespace.h>

namespace rad::model{

//Constructor / Destructor
Measure::Measure(rad::Node* node_radio){
  //---------------------------

  this->radio_struct = node_radio->get_radio_struct();

  //---------------------------
  this->init_plot();
}
Measure::~Measure(){}

//Main function
void Measure::import_measure(){
  rad::structure::Measure* measure = &radio_struct->model.measure;
  //---------------------------

  //Import file model data
  measure->vec_data = utl::file::read_vector(measure->path);
  this->find_measure_bound();
  this->update_plot();

  //---------------------------
}
void Measure::export_measure(){
  rad::structure::Measure* measure = &radio_struct->model.measure;
  //---------------------------

  utl::file::write_vector(measure->path, measure->vec_data);

  //---------------------------
}
void Measure::clear_measure(){
  rad::structure::Measure* measure = &radio_struct->model.measure;
  //---------------------------

  //Import file model data
  measure->vec_data.clear();
  this->clear_plot();

  //---------------------------
}

//Subfunction
void Measure::find_measure_bound(){
  rad::structure::Optimization* model = &radio_struct->model.optim;
  rad::structure::Measure* measure = &radio_struct->model.measure;
  //---------------------------

  for(int i=0; i<measure->vec_data.size(); i++){
    float& R = measure->vec_data[i].x;
    if(R < 0) continue;
    if(R < model->x.bound[0]) model->x.bound[0] = R;
    if(R > model->x.bound[1]) model->x.bound[1] = R;

    float& It = measure->vec_data[i].y;
    if(It < 0) continue;
    if(It < model->y.bound[0]) model->y.bound[0] = It;
    if(It > model->y.bound[1]) model->y.bound[1] = It;
  }

  //---------------------------
}
void Measure::clean_measure(){
  rad::structure::Measure* measure = &radio_struct->model.measure;
  //---------------------------

  std::vector<glm::vec3>& vec_data = measure->vec_data;
  for(int i=0; i<vec_data.size(); i++){
    glm::vec3& data = vec_data[i];

    if(data.x < 0 || data.y < 0){
      data = glm::vec3(-1, -1, -1);
    }
  }

  //---------------------------
}

//Plot function
void Measure::init_plot(){
  rad::structure::Optimization* model = &radio_struct->model.optim;
  rad::structure::Measure* measure = &radio_struct->model.measure;
  //---------------------------

  //I(R)
  measure->IfR.title = "I(R)";
  measure->IfR.highlight = vec2(0, 0);
  measure->IfR.x.resolution = 0.01f;
  measure->IfR.x.min = 0.0f;
  measure->IfR.x.max = 5.0f;
  measure->IfR.x.size = static_cast<int>((measure->IfR.x.max - measure->IfR.x.min) / measure->IfR.x.resolution) + 1;
  measure->IfR.x.data = vector<float>(measure->IfR.x.size, 0.0f);
  measure->IfR.y.data = vector<float>(measure->IfR.x.size, 0.0f);

  //I(It)
  measure->IfIt.title = "I(It)";
  measure->IfIt.x.resolution = 1.0f;
  measure->IfIt.x.min = 0.0f;
  measure->IfIt.x.max = 90.0f;
  measure->IfIt.x.size = static_cast<int>((measure->IfIt.x.max - measure->IfIt.x.min) / measure->IfIt.x.resolution) + 1;
  measure->IfIt.x.data = vector<float>(measure->IfIt.x.size, 0.0f);
  measure->IfIt.y.data = vector<float>(measure->IfIt.x.size, 0.0f);

  //I(R, It)
  measure->IfRIt.title = "I(R, It)";
  measure->IfRIt.x.resolution = 0.01f;
  measure->IfRIt.x.min = 0.0f;
  measure->IfRIt.x.max = 5.0f;
  measure->IfRIt.x.size = static_cast<int>((measure->IfRIt.x.max - measure->IfRIt.x.min) / measure->IfRIt.x.resolution) + 1;
  measure->IfRIt.y.resolution = 1.0f;
  measure->IfRIt.y.min = 0.0f;
  measure->IfRIt.y.max = 90.0f;
  measure->IfRIt.y.size = static_cast<int>((measure->IfRIt.y.max - measure->IfRIt.y.min) / measure->IfRIt.y.resolution) + 1;
  measure->IfRIt.z.min = 0.0f;
  measure->IfRIt.z.max = 2500.0f;
  measure->IfRIt.z.size = measure->IfRIt.x.size * measure->IfRIt.y.size;
  measure->IfRIt.z.data = vector<float>(measure->IfRIt.z.size, 0.0f);

  //Measure
  measure->vec_data = vector<vec3>(measure->IfRIt.z.size, vec3(-1, -1, -1));
  model->x.bound = vec2(1000, -1);
  model->x.current = 1;
  model->y.bound = vec2(0, 90);
  model->y.current = 40;

  //---------------------------
}
void Measure::reset_plot(){
  rad::structure::Optimization* model = &radio_struct->model.optim;
  rad::structure::Measure* measure = &radio_struct->model.measure;
  //---------------------------

  //I(R)
  for(int i=0; i<measure->IfR.x.data.size(); i++){
    measure->IfR.x.data[i] = 0;
  }
  for(int i=0; i<measure->IfR.y.data.size(); i++){
    measure->IfR.y.data[i] = 0;
  }

  //I(It)
  for(int i=0; i<measure->IfIt.x.data.size(); i++){
    measure->IfIt.x.data[i] = 0;
  }
  for(int i=0; i<measure->IfIt.y.data.size(); i++){
    measure->IfIt.y.data[i] = 0;
  }

  //I(R, It)
  for(int i=0; i<measure->IfRIt.z.data.size(); i++){
    measure->IfRIt.z.data[i] = 0;
  }

  //---------------------------
}
void Measure::update_plot(){
  rad::structure::Measure* measure = &radio_struct->model.measure;
  rad::structure::Optimization* model = &radio_struct->model.optim;
  //---------------------------

  this->reset_plot();

  //Fill model plot data
  for(int i=0; i<measure->vec_data.size(); i++){
    float& R = measure->vec_data[i].x;
    float& It = measure->vec_data[i].y;
    float& I = measure->vec_data[i].z;
    if(R == -1) continue;

    measure->IfRIt.z.data[i] = I;

    //I(R)
    if(R > model->x.bound[0] && R < model->x.bound[1]) // R inside user defined bounds
    if(It > model->y.current && It < model->y.current + 5){ //All data between It current + 5 degrees
      int index = static_cast<int>(std::round(R / measure->IfR.x.resolution));
      measure->IfR.x.data[index] = R;
      measure->IfR.y.data[index] = I;

      if(R > model->x.current && R < model->x.current + 0.05){
        measure->IfR.highlight = vec2(R, I);
      }
    }

    //I(It)
    if(It > model->y.bound[0] && It < model->y.bound[1]) // It It inside user defined bounds
    if(R > model->x.current && R < model->x.current + 0.05){ //All data between R current + 0.05m
      int index = static_cast<int>(std::round(It / measure->IfIt.x.resolution));
      measure->IfIt.x.data[index] = It;
      measure->IfIt.y.data[index] = I;
    }
  }

  //---------------------------
}
void Measure::clear_plot(){
  rad::structure::Optimization* model = &radio_struct->model.optim;
  rad::structure::Measure* measure = &radio_struct->model.measure;
  //---------------------------

  //I(R)
  for(int i=0; i<measure->IfR.x.data.size(); i++){
    measure->IfR.x.data[i] = 0;
  }
  for(int i=0; i<measure->IfR.y.data.size(); i++){
    measure->IfR.y.data[i] = 0;
  }

  //I(It)
  for(int i=0; i<measure->IfIt.x.data.size(); i++){
    measure->IfIt.x.data[i] = 0;
  }
  for(int i=0; i<measure->IfIt.y.data.size(); i++){
    measure->IfIt.y.data[i] = 0;
  }

  //I(R, It)
  for(int i=0; i<measure->IfRIt.z.data.size(); i++){
    measure->IfRIt.z.data[i] = 0;
    measure->vec_data[i] = vec3(-1, -1, -1);
  }

  //---------------------------
}

}
