#include "Measure.h"

#include <K4N/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Measure::Measure(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();

  //---------------------------
  this->init();
}
Measure::~Measure(){}

//Main function
void Measure::init(){
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------

  //I(R)
  model->IfR.title = "I(R)";
  model->IfR.x.resolution = 0.01f;
  model->IfR.x.min = 0.0f;
  model->IfR.x.max = 5.0f;
  model->IfR.x.size = static_cast<int>((model->IfR.x.max - model->IfR.x.min) / model->IfR.x.resolution) + 1;
  model->IfR.x.data = vector<float>(model->IfR.x.size, 0.0f);
  model->IfR.y.data = vector<float>(model->IfR.x.size, 0.0f);

  //I(It)
  model->IfIt.title = "I(It)";
  model->IfIt.x.resolution = 1.0f;
  model->IfIt.x.min = 0.0f;
  model->IfIt.x.max = 90.0f;
  model->IfIt.x.size = static_cast<int>((model->IfIt.x.max - model->IfIt.x.min) / model->IfIt.x.resolution) + 1;
  model->IfIt.x.data = vector<float>(model->IfIt.x.size, 0.0f);
  model->IfIt.y.data = vector<float>(model->IfIt.x.size, 0.0f);

  //I(R, It)
  model->IfRIt.title = "I(R, It)";
  model->IfRIt.x.resolution = 0.01f;
  model->IfRIt.x.min = 0.0f;
  model->IfRIt.x.max = 5.0f;
  model->IfRIt.x.size = static_cast<int>((model->IfRIt.x.max - model->IfRIt.x.min) / model->IfRIt.x.resolution) + 1;
  model->IfRIt.y.resolution = 1.0f;
  model->IfRIt.y.min = 0.0f;
  model->IfRIt.y.max = 90.0f;
  model->IfRIt.y.size = static_cast<int>((model->IfRIt.y.max - model->IfRIt.y.min) / model->IfRIt.y.resolution) + 1;
  model->IfRIt.z.min = 0.0f;
  model->IfRIt.z.max = 2500.0f;
  model->IfRIt.z.size = model->IfRIt.x.size * model->IfRIt.y.size;
  model->IfRIt.z.data = vector<float>(model->IfRIt.z.size, 0.0f);

  //Measure
  model->vec_data = vector<vec3>(model->IfRIt.z.size, vec3(-1, -1, -1));
  model->x.bound = vec2(1000, -1);
  model->x.current = 1;
  model->y.bound = vec2(0, 90);
  model->y.current = 40;

  //---------------------------
}
void Measure::import(){
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------

  //Import file model data
  model->vec_data = utl::file::read_vector(model->path);
  this->update_plot();
  this->find_model_bounds();

  //---------------------------
}
void Measure::export(){
  //---------------------------

  utl::file::write_vector(k4n_struct->matching.model.path, k4n_struct->matching.model.vec_data);

  //---------------------------
}
void Measure::update(){
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------

  //Fill model plot data
  for(int i=0; i<model->vec_data.size(); i++){
    float& R = model->vec_data[i].x;
    float& It = model->vec_data[i].y;
    float& I = model->vec_data[i].z;
    if(R == -1) continue;

    model->IfRIt.z.data[i] = I;

    //I(R)
    if(It > model->y.current && It < model->y.current + 5){
      int index = static_cast<int>(std::round(R / model->IfR.x.resolution));
      model->IfR.x.data[index] = R;
      model->IfR.y.data[index] = I;

      if(R > model->x.current && R < model->x.current + 0.05){
        model->IfR.highlight = vec2(R, I);
      }
    }

    //I(It)
    if(R > model->x.current && R < model->x.current + 0.05){
      int index = static_cast<int>(std::round(It / model->IfIt.x.resolution));
      model->IfIt.x.data[index] = It;
      model->IfIt.y.data[index] = I;
    }
  }

  //---------------------------
}

//Subfunction
void Measure::find_bounds(){
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------

  for(int i=0; i<model->vec_data.size(); i++){
    float& R = model->vec_data[i].x;
    if(R == -1) continue;
    if(R < model->x.bound[0]) model->x.bound[0] = R;
    if(R > model->x.bound[1]) model->x.bound[1] = R;

    float& It = model->vec_data[i].y;
    if(It == -1) continue;
    if(It < model->y.bound[0]) model->y.bound[0] = It;
    if(It > model->y.bound[1]) model->y.bound[1] = It;
  }

  //---------------------------
}

}
