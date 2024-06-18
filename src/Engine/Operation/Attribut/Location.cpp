#include "Location.h"

#include <Data/Namespace.h>


namespace ope::attribut{

// Constructor / Destructor
Location::Location(){}
Location::~Location(){}

//Main function
glm::vec3 Location::compute_centroid(utl::base::Element* element){
  if(element == nullptr) return glm::vec3(0);
  //---------------------------

  glm::vec3 centroid;
  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    centroid = compute_centroid(set);
  }
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    centroid = compute_centroid(entity);
  }

  //---------------------------
  return centroid;
}
glm::vec3 Location::compute_centroid(dat::base::Set* set){
  //---------------------------

  glm::vec3 centroid = glm::vec3(0, 0, 0);

  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);
    glm::vec3 entity_COM = compute_centroid(entity);

    for(int j=0; j<3; j++){
      centroid[j] += entity_COM[j];
    }
  }

  for(int i=0; i<3; i++){
    centroid[i] /= set->list_entity.size();
  }

  //---------------------------
  set->pose.COM = centroid;
  return centroid;
}
glm::vec3 Location::compute_centroid(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  utl::base::Pose* pose = &entity->pose;
  //---------------------------

  std::vector<glm::vec3>& xyz = data->xyz;

  //Compute raw centroid
  glm::vec3 centroid = glm::vec3(0, 0, 0);
  for(int i=0; i<xyz.size(); i++){
    centroid += xyz[i];
  }
  centroid /= xyz.size();

  //Transform the centroid by the model matrix
  glm::vec4 centroid_h = glm::vec4(centroid, 1.0f);
  centroid_h = pose->model * centroid_h;

  //---------------------------
  return glm::vec3(centroid_h);
}
void Location::compute_MinMax(dat::base::Set* set){
  //---------------------------

  glm::vec3 centroid = glm::vec3(0, 0, 0);
  glm::vec3 min = glm::vec3(1000000, 1000000, 1000000);
  glm::vec3 max = glm::vec3(-1000000, -1000000, -1000000);

  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);
    utl::base::Pose* pose = &entity->pose;
    this->compute_MinMax(entity);

    for(int j=0; j<3; j++){
      if(pose->min[j] <= min[j]) min[j] = pose->min[j];
      if(pose->max[j] >= max[j]) max[j] = pose->max[j];
      centroid[j] += pose->COM[j];
    }

  }

  for(int j=0;j<3;j++){
    centroid[j] /= set->list_entity.size();
  }

  //---------------------------
  set->pose.min = min;
  set->pose.max = max;
  set->pose.COM = centroid;
}
void Location::compute_MinMax(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  utl::base::Pose* pose = &entity->pose;
  //---------------------------

  std::vector<glm::vec3>& XYZ = data->xyz;
  if(XYZ.size() == 0) return;

  glm::vec3 centroid = glm::vec3(0, 0, 0);
  glm::vec3 min = glm::vec3(1000000, 1000000, 1000000);
  glm::vec3 max = glm::vec3(-1000000, -1000000, -1000000);

  for(int i=0; i<XYZ.size(); i++){
    vec4 xys_h = vec4(XYZ[i].x, XYZ[i].y, XYZ[i].z, 1);
    xys_h = xys_h * pose->model;

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
  pose->min = min;
  pose->max = max;
  pose->COM = centroid;
}
void Location::compute_range(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  std::vector<float>& R = data->R;
  std::vector<glm::vec3>& xyz = data->xyz;

  R = std::vector<float>(xyz.size(), 0.0f);
  for(int i=0; i<xyz.size(); i++){
    float dist = math::distance_from_origin(xyz[i]);
    R[i] = dist;
  }

  //---------------------------
}
void Location::compute_incidence_angle(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  std::vector<float>& It = data->It;
  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec3>& Nxyz = data->Nxyz;

  It = std::vector<float>(xyz.size(), 0.0f);
  for(int i=0; i<xyz.size(); i++){
    float angle = math::compute_It(xyz[i], Nxyz[i], glm::vec3(0, 0, 0));
    It[i] = angle;
  }

  //---------------------------
}
void Location::set_unicolor(dat::base::Entity* entity){
  if(entity == nullptr) return;
  utl::base::Data* data = &entity->data;
  //---------------------------

  for(int i=0; i<data->rgb.size(); i++){
    data->rgb[i] = data->unicolor;
  }

  //---------------------------
}
void Location::retrieve_z_vector(dat::base::Entity* entity, std::vector<float>& z_vec){
  utl::base::Data* data = &entity->data;
  utl::base::Pose* pose = &entity->pose;
  //---------------------------

  std::vector<glm::vec3>& xyz = data->xyz;
  z_vec = std::vector<float>(xyz.size());

  #pragma omp parallel for
  for(int i=0; i<xyz.size(); i++){
    vec4 xyz_h = vec4(xyz[i].x, xyz[i].y, xyz[i].z, 1);
    xyz_h = xyz_h * pose->model;
    z_vec[i] = xyz_h.z;
  }

  //---------------------------
}

}
