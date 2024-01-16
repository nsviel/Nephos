#include "Attribut.h"


namespace eng::ope{

// Constructor / Destructor
Attribut::Attribut(){}
Attribut::~Attribut(){}

//Main function
void Attribut::compute_MinMax(entity::Object* object){
  vector<vec3>& XYZ = object->xyz;
  if(XYZ.size() == 0) return;
  //---------------------------

  vec3 centroid = vec3(0, 0, 0);
  vec3 min = vec3(1000000, 1000000, 1000000);
  vec3 max = vec3(-1000000, -1000000, -1000000);

  for(int i=0; i<XYZ.size(); i++){
    vec4 xys_h = vec4(XYZ[i].x, XYZ[i].y, XYZ[i].z, 1);
    xys_h = xys_h * object->model;

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
  object->min = min;
  object->max = max;
  object->COM = centroid;
}
void Attribut::set_visibility(eng::base::Set* set, bool visibility){
  //---------------------------

  for(int i=0; i<set->list_entity.size(); i++){
    entity::Object* object = (entity::Object*)*next(set->list_entity.begin(), i);
    object->is_visible = visibility;
  }

  //---------------------------
}
void Attribut::set_unicolor(entity::Object* object){
  //---------------------------

  for(int i=0; i<object->rgb.size(); i++){
    object->rgb[i] = object->unicolor;
  }

  //---------------------------
}
vector<float> Attribut::retrieve_z_vector(entity::Object* object){
  vector<vec3>& xyz = object->xyz;
  vector<float> z_vec;
  //---------------------------

  for(int i=0; i<xyz.size(); i++){
    vec4 xyz_h = vec4(xyz[i].x, xyz[i].y, xyz[i].z, 1);
    xyz_h = xyz_h * object->model;
    z_vec.push_back(xyz_h.z);
  }

  //---------------------------
  return z_vec;
}

}
