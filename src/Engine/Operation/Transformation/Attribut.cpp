#include "Attribut.h"


namespace eng::ope{

// Constructor / Destructor
Attribut::Attribut(){}
Attribut::~Attribut(){}

//Main function
void Attribut::compute_centroid(utl::type::Set* set){
  if(set == nullptr) return;
  //---------------------------

  vec3 centroid = vec3(0, 0, 0);

  for(int i=0; i<set->list_entity.size(); i++){
    utl::type::Entity* entity = *next(set->list_entity.begin(), i);
    vec3 entity_COM = compute_centroid(entity);

    for(int j=0; j<3; j++){
      centroid[j] += entity_COM[j];
    }
  }

  for(int i=0; i<3; i++){
    centroid[i] /= set->list_entity.size();
  }

  //---------------------------
  return centroid;
}
vec3 Attribut::compute_centroid(utl::type::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  vector<vec3>& XYZ = entity->data.xyz;
  vec3 centroid = vec3(0, 0, 0);

  for(int i=0; i<XYZ.size(); i++){
    vec4 xys_h = vec4(XYZ[i].x, XYZ[i].y, XYZ[i].z, 1);
    xys_h = xys_h * entity->data.model;

    for(int j=0; j<3; j++){
      centroid[j] += xys_h[j];
    }
  }

  for(int j=0;j<3;j++){
    centroid[j] /= XYZ.size();
  }

  //---------------------------
  return centroid;
}
void Attribut::compute_MinMax(utl::type::Entity* entity){
  if(entity == nullptr) return;
  utl::type::Data* data = entity->get_data();
  //---------------------------

  vector<vec3>& XYZ = data->xyz;
  if(XYZ.size() == 0) return;

  vec3 centroid = vec3(0, 0, 0);
  vec3 min = vec3(1000000, 1000000, 1000000);
  vec3 max = vec3(-1000000, -1000000, -1000000);

  for(int i=0; i<XYZ.size(); i++){
    vec4 xys_h = vec4(XYZ[i].x, XYZ[i].y, XYZ[i].z, 1);
    xys_h = xys_h * data->model;

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
  data->min = min;
  data->max = max;
  data->COM = centroid;
}
void Attribut::set_unicolor(utl::type::Entity* entity){
  if(entity == nullptr) return;
  utl::type::Data* data = entity->get_data();
  //---------------------------

  for(int i=0; i<data->rgb.size(); i++){
    data->rgb[i] = data->unicolor;
  }

  //---------------------------
}
vector<float> Attribut::retrieve_z_vector(utl::type::Entity* entity){
  if(entity == nullptr) return vector<float>();
  utl::type::Data* data = entity->get_data();
  //---------------------------

  vector<vec3>& xyz = data->xyz;
  vector<float> z_vec;

  for(int i=0; i<xyz.size(); i++){
    vec4 xyz_h = vec4(xyz[i].x, xyz[i].y, xyz[i].z, 1);
    xyz_h = xyz_h * data->model;
    z_vec.push_back(xyz_h.z);
  }

  //---------------------------
  return z_vec;
}

}
