#include "Attribut.h"


namespace eng::ope{

// Constructor / Destructor
Attribut::Attribut(){}
Attribut::~Attribut(){}

//Main function
void Attribut::compute_MinMax(entity::Object* object){
  vector<vec3>& XYZ = object->data->xyz;
  if(XYZ.size() == 0) return;
  //---------------------------

  vec3 centroid = vec3(0, 0, 0);
  vec3 min = vec3(1000000, 1000000, 1000000);
  vec3 max = vec3(-1000000, -1000000, -1000000);

  for(int i=0; i<XYZ.size(); i++){
    vec4 xys_h = vec4(XYZ[i].x, XYZ[i].y, XYZ[i].z, 1);
    xys_h = xys_h * object->data->model;

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
  object->data->min = min;
  object->data->max = max;
  object->data->COM = centroid;
}
void Attribut::set_unicolor(entity::Object* object){
  //---------------------------

  for(int i=0; i<object->data->rgb.size(); i++){
    object->data->rgb[i] = object->data->unicolor;
  }

  //---------------------------
}
vector<float> Attribut::retrieve_z_vector(entity::Object* object){
  vector<vec3>& xyz = object->data->xyz;
  vector<float> z_vec;
  //---------------------------

  for(int i=0; i<xyz.size(); i++){
    vec4 xyz_h = vec4(xyz[i].x, xyz[i].y, xyz[i].z, 1);
    xyz_h = xyz_h * object->data->model;
    z_vec.push_back(xyz_h.z);
  }

  //---------------------------
  return z_vec;
}

}
