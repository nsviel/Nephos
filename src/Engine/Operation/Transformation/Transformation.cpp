#include "Transformation.h"

#include <Utility/Function/Math/fct_math.h>


namespace eng::ope{

// Constructor / Destructor
Transformation::Transformation(){}
Transformation::~Transformation(){}

// Translation
void Transformation::make_translation(eng::data::Object* object, vec3 trans){
  if(object == nullptr) return;
  //---------------------------

  glm::mat4 translation = get_translation_mat(trans);

  object->COM += trans;
  object->root += trans;
  object->trans *= translation;
  object->model *= translation;

  //---------------------------
}
void Transformation::make_translation(eng::data::Object* object, mat4 translation){
  if(object == nullptr) return;
  //---------------------------

  vec3 trans = vec3(translation[0][3], translation[1][3], translation[2][3]);

  object->COM += trans;
  object->root += trans;
  object->trans *= translation;
  object->model *= translation;

  //---------------------------
}

//Rotation
void Transformation::make_rotation(eng::data::Object* object, vec3 COM, vec3 radian){
  if(object == nullptr) return;
  //---------------------------

  mat4 rotation = get_rotation_mat(radian);
  mat4 COM_mat = get_translation_mat_neye(COM);

  object->rotat *= rotation;
  object->model -= COM_mat;
  object->model *= rotation;
  object->model += COM_mat;

  //---------------------------
}
void Transformation::make_rotation(eng::data::Object* object, vec3 degree){
  if(object == nullptr) return;
  //---------------------------

  vec3& COM = object->COM;
  vec3 radian = math::degree_to_radian(degree);
  mat4 rotation = get_rotation_mat(radian);
  mat4 COM_mat = get_translation_mat_neye(COM);

  object->rotat *= rotation;
  object->model -= COM_mat;
  object->model *= rotation;
  object->model += COM_mat;

  //---------------------------
}
void Transformation::make_rotation(eng::data::Object* object, vec3 COM, mat4 rotation){
  if(object == nullptr) return;
  //---------------------------

  //vec3& COM = object->COM;
  mat4 COM_mat = get_translation_mat_neye(COM);

  object->rotat *= rotation;
  object->model -= COM_mat;
  object->model *= rotation;
  object->model += COM_mat;

  //---------------------------
}
void Transformation::make_rotation_axe_X(eng::data::Object* object, float degree){
  if(object == nullptr) return;
  //---------------------------

  float radian = math::degree_to_radian(degree);

  // Matrice de rotation locale autour de l'axe x
  glm::mat4 rotationMatrixXLocal = glm::rotate(glm::mat4(1.0f), radian, glm::vec3(1.0f, 0.0f, 0.0f));

  // Obtenez la partie de translation de la matrice modèle actuelle
  glm::vec3 translation = glm::vec3(object->model[3]);

  // Appliquez la nouvelle rotation locale à la matrice modèle
  object->model = glm::translate(glm::mat4(1.0f), translation) * rotationMatrixXLocal * object->model;

  // Mettez à jour les composantes de rotation cumulatives
  object->rotat = rotationMatrixXLocal * object->rotat;

  // Mettez à jour les composantes de translation cumulatives
  object->trans = glm::translate(glm::mat4(1.0f), translation) * object->trans;

  //---------------------------
}

//Scaling
void Transformation::make_scaling(eng::data::Object* object, float scale){
  if(object == nullptr) return;
  //---------------------------

  glm::mat4 scaling(1.0);
  scaling[0][0] = scale;
  scaling[1][1] = scale;
  scaling[2][2] = scale;

  object->scale *= scaling;
  object->model *= scaling;

  //---------------------------
}

//Transformation
void Transformation::make_transformation(eng::data::Object* object, vec3 COM, mat4 translation, mat4 rotation){
  if(object == nullptr) return;
  //---------------------------

  mat4 COM_mat = get_translation_mat_neye(COM);

  object->model = translation;
  object->model -= COM_mat;
  object->model *= rotation;
  object->model += COM_mat;

  //---------------------------
}

//Subfunction
mat4 Transformation::get_translation_mat(vec3 trans){
  glm::mat4 translation(1.0);
  //---------------------------

  translation[0][3] = trans.x;
  translation[1][3] = trans.y;
  translation[2][3] = trans.z;

  //---------------------------
  return translation;
}
mat4 Transformation::get_translation_mat_neye(vec3 trans){
  glm::mat4 translation(0.0);
  //---------------------------

  translation[0][3] = trans.x;
  translation[1][3] = trans.y;
  translation[2][3] = trans.z;

  //---------------------------
  return translation;
}
mat4 Transformation::get_rotation_mat(vec3 r){
  glm::mat4 Rx(1.0);
  glm::mat4 Ry(1.0);
  glm::mat4 Rz(1.0);
  //---------------------------

  Rx[1][1]=cos(r.x);
  Rx[2][1]=sin(r.x);
  Rx[1][2]=-sin(r.x);
  Rx[2][2]=cos(r.x);

  Ry[0][0]=cos(r.y);
  Ry[0][2]=sin(r.y);
  Ry[2][0]=-sin(r.y);
  Ry[2][2]=cos(r.y);

  Rz[0][0]=cos(r.z);
  Rz[1][0]=sin(r.z);
  Rz[0][1]=-sin(r.z);
  Rz[1][1]=cos(r.z);

  glm::mat4 rotation = Rx * Ry * Rz;

  //---------------------------
  return rotation;
}

}
