#include "Location.h"

#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::atr{

// Constructor / Destructor
Location::Location(){
  //---------------------------

  this->atr_field = new dat::atr::Field();

  //---------------------------
}
Location::~Location(){}

//Main function
void Location::compute_centroid(dat::base::Entity& entity){
  utl::base::Data& data = *entity.data;
  //---------------------------

  //Compute raw centroid
  glm::vec3& centroid = data.centroid;
  glm::vec3 temp_centroid(0.0f, 0.0f, 0.0f);

  // Parallel sum of xyz vectors
  #pragma omp parallel for reduction(+:temp_centroid)
  for(auto& xyz : data.xyz){
    temp_centroid += xyz;
  }

  // Compute average
  std::unique_lock<std::mutex> lock(data.mutex);
  centroid = temp_centroid / static_cast<float>(data.xyz.size());

  //---------------------------
}
void Location::compute_COM(utl::base::Element& element){
  //---------------------------

  // Attempt to cast to dat::base::Set
  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(&element)){
    this->compute_COM(*set);
  }
  // Attempt to cast to dat::base::Entity
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(&element)){
   this->compute_COM(*entity);
  }

  //---------------------------
}
void Location::compute_COM(dat::base::Set& set){
  //---------------------------

  glm::vec3 COM = glm::vec3(0, 0, 0);

  for(auto& entity : set.list_entity){
    this->compute_COM(*entity);
    COM += entity->pose->COM;
  }

  COM /= set.list_entity.size();

  //---------------------------
  set.pose->COM = COM;
}
void Location::compute_COM(dat::base::Entity& entity){
  //---------------------------

  utl::base::Data& data = *entity.data;
  utl::base::Pose& pose = *entity.pose;

  this->compute_centroid(entity);

  //Transform the centroid by the model matrix
  glm::vec4 centroid = glm::vec4(data.centroid, 1.0f);
  pose.COM = centroid * pose.model;

  //---------------------------
}
void Location::compute_MinMax(dat::base::Set& set){
  utl::base::Pose& pose = *set.pose;
  //---------------------------

  glm::vec3 centroid = glm::vec3(0, 0, 0);
  glm::vec3 min = glm::vec3(1000000, 1000000, 1000000);
  glm::vec3 max = glm::vec3(-1000000, -1000000, -1000000);

  for(auto& entity : set.list_entity){
    utl::base::Pose& pose = *entity->pose;
    this->compute_MinMax(*entity);

    for(int j=0; j<3; j++){
      if(pose.min[j] <= min[j]) min[j] = pose.min[j];
      if(pose.max[j] >= max[j]) max[j] = pose.max[j];
      centroid[j] += pose.COM[j];
    }
  }

  for(int j=0;j<3;j++){
    centroid[j] /= set.list_entity.size();
  }

  //---------------------------
  pose.min = min;
  pose.max = max;
  pose.COM = centroid;
}
void Location::compute_MinMax(dat::base::Entity& entity){
  utl::base::Data& data = *entity.data;
  utl::base::Pose& pose = *entity.pose;
  //---------------------------

  std::vector<glm::vec3>& XYZ = data.xyz;
  if(XYZ.size() == 0) return;

  glm::vec3 centroid = glm::vec3(0, 0, 0);
  glm::vec3 min = glm::vec3(1000000, 1000000, 1000000);
  glm::vec3 max = glm::vec3(-1000000, -1000000, -1000000);

  for(int i=0; i<XYZ.size(); i++){
    glm::vec4 xys_h = glm::vec4(XYZ[i].x, XYZ[i].y, XYZ[i].z, 1);
    xys_h = xys_h * pose.model;

    for(int j=0; j<3; j++){
      if(xys_h[j] <= min[j]) min[j] = xys_h[j];
      if(xys_h[j] >= max[j]) max[j] = xys_h[j];
      centroid[j] += xys_h[j];
    }
  }

  for(int j=0;j<3;j++){
    centroid[j] /= XYZ.size();
  }

  //---------------------------
  pose.min = min;
  pose.max = max;
  pose.COM = centroid;
}
void Location::compute_height(dat::base::Entity& entity){
  utl::base::Data& data = *entity.data;
  utl::base::Pose& pose = *entity.pose;
  //---------------------------

  //Retrieve field
  std::unique_ptr<std::vector<float>> vec_h_ptr = atr_field->get_field_data(data, "H");
  if(!vec_h_ptr || !vec_h_ptr->empty()) return;
  std::vector<float>& vec_h = *vec_h_ptr;

  //Set length
  std::vector<glm::vec3>& xyz = data.xyz;
  vec_h = std::vector<float>(data.xyz.size());

  #pragma omp parallel for
  for(int i=0; i<xyz.size(); i++){
    glm::vec4 xyz_h = glm::vec4(xyz[i].x, xyz[i].y, xyz[i].z, 1);
    xyz_h = xyz_h * pose.model;
    vec_h[i] = xyz_h.z;
  }

  //---------------------------
}
void Location::compute_range(dat::base::Entity& entity){
  utl::base::Data& data = *entity.data;
  //---------------------------

  //Retrieve field
  std::unique_ptr<std::vector<float>> vec_R_ptr = atr_field->get_field_data(data, "R");
  if(!vec_R_ptr || !vec_R_ptr->empty()) return;
  std::vector<float>& vec_R = *vec_R_ptr;

  //Set length
  std::vector<glm::vec3>& xyz = data.xyz;
  vec_R.resize(xyz.size(), 0.0f);

  #pragma omp parallel for
  for(int i=0; i<xyz.size(); i++){
    float dist = glm::length(xyz[i]);
    vec_R[i] = dist;
  }

  //---------------------------
}
void Location::compute_incidence_angle(dat::base::Entity& entity){
  utl::base::Data& data = *entity.data;
  //---------------------------

  std::unique_ptr<std::vector<float>> vec_R_ptr = atr_field->get_field_data(data, "R");
  std::unique_ptr<std::vector<float>> vec_It_ptr = atr_field->get_field_data(data, "It");
  if(!vec_R_ptr || !vec_It_ptr) return;

  std::vector<float>& It = *vec_It_ptr;
  std::vector<float>& R = *vec_R_ptr;
  std::vector<glm::vec3>& xyz = data.xyz;
  std::vector<glm::vec3>& Nxyz = data.Nxyz;

  It = std::vector<float>(xyz.size(), 0.0f);
  for(int i=0; i<xyz.size(); i++){
    float angle = math::compute_It(xyz[i], Nxyz[i], R[i]);
    It[i] = angle;
  }

  //---------------------------
}

}
