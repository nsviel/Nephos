#include "Attribut.h"


namespace eng::ope{

// Constructor / Destructor
Attribut::Attribut(){}
Attribut::~Attribut(){}

//Main function
void Attribut::compute_MinMax(eng::structure::Object* object){
  vector<vec3>& XYZ = object->xyz;
  if(XYZ.size() == 0) return;
  //---------------------------

  vec3 centroid = vec3(0, 0, 0);
  vec3 min = XYZ[0];
  vec3 max = XYZ[0];

  for(int i=0; i<XYZ.size(); i++){
    for(int j=0; j<3; j++){
      if(XYZ[i][j] <= min[j]) min[j] = XYZ[i][j];
      if(XYZ[i][j] >= max[j]) max[j] = XYZ[i][j];
      centroid[j] += XYZ[i][j];
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
void Attribut::set_visibility(eng::structure::Set* set, bool visibility){
  //---------------------------

  for(int i=0; i<set->list_entity.size(); i++){
    eng::structure::Object* object = (eng::structure::Object*)*next(set->list_entity.begin(), i);
    object->is_visible = visibility;
  }

  //---------------------------
}
void Attribut::set_unicolor(eng::structure::Object* object){
  //---------------------------

  for(int i=0; i<object->rgb.size(); i++){
    object->rgb[i] = object->unicolor;
  }

  //---------------------------
}

}
