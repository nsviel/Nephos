#include "Transformation.h"

#include <Utility/Function/Math/fct_math.h>


namespace eng::ope{

// Constructor / Destructor
Transformation::Transformation(){}
Transformation::~Transformation(){}

// Translation
void Transformation::make_translation(utl::type::Data* data, vec3 trans){
  if(data == nullptr) return;
  //---------------------------

  glm::mat4 translation = get_translation_mat(trans);

  data->COM += trans;
  data->root += trans;
  data->trans *= translation;
  data->model *= translation;

  //---------------------------
}
void Transformation::make_translation(utl::type::Data* data, mat4 translation){
  if(data == nullptr) return;
  //---------------------------

  vec3 trans = vec3(translation[0][3], translation[1][3], translation[2][3]);

  data->COM += trans;
  data->root += trans;
  data->trans *= translation;
  data->model *= translation;

  //---------------------------
}

//Rotation
void Transformation::make_rotation(utl::type::Data* data, vec3 COM, vec3 radian){
  if(data == nullptr) return;
  //---------------------------

  mat4 rotation = get_rotation_mat(radian);
  mat4 COM_mat = get_translation_mat_neye(COM);

  data->rotat *= rotation;
  data->model -= COM_mat;
  data->model *= rotation;
  data->model += COM_mat;

  //---------------------------
}
void Transformation::make_rotation(utl::type::Data* data, vec3 degree){
  if(data == nullptr) return;
  //---------------------------

  vec3& COM = data->COM;
  vec3 radian = math::degree_to_radian(degree);
  mat4 rotation = get_rotation_mat(radian);
  mat4 COM_mat = get_translation_mat_neye(COM);

  data->rotat *= rotation;
  data->model -= COM_mat;
  data->model *= rotation;
  data->model += COM_mat;

  //---------------------------
}
void Transformation::make_rotation(utl::type::Data* data, vec3 COM, mat4 rotation){
  if(data == nullptr) return;
  //---------------------------

  //vec3& COM = data->COM;
  mat4 COM_mat = get_translation_mat_neye(COM);

  data->rotat *= rotation;
  data->model -= COM_mat;
  data->model *= rotation;
  data->model += COM_mat;

  //---------------------------
}
void Transformation::make_rotation_axe_X(utl::type::Data* data, float degree){
  if(data == nullptr) return;
  //---------------------------

  float radian = math::degree_to_radian(degree);

  // Matrice de rotation locale autour de l'axe x
  glm::mat4 rotationMatrixXLocal = glm::rotate(glm::mat4(1.0f), radian, glm::vec3(1.0f, 0.0f, 0.0f));

  // Obtenez la partie de translation de la matrice modèle actuelle
  glm::vec3 translation = glm::vec3(data->model[3]);

  // Appliquez la nouvelle rotation locale à la matrice modèle
  data->model = glm::translate(glm::mat4(1.0f), translation) * rotationMatrixXLocal * data->model;

  // Mettez à jour les composantes de rotation cumulatives
  data->rotat = rotationMatrixXLocal * data->rotat;

  // Mettez à jour les composantes de translation cumulatives
  data->trans = glm::translate(glm::mat4(1.0f), translation) * data->trans;

  //---------------------------
}

//Scaling
void Transformation::make_scaling(utl::type::Data* data, float scale){
  if(data == nullptr) return;
  //---------------------------

  glm::mat4 scaling(1.0);
  scaling[0][0] = scale;
  scaling[1][1] = scale;
  scaling[2][2] = scale;

  data->scale *= scaling;
  data->model *= scaling;

  //---------------------------
}

//Transformation
void Transformation::make_transformation(utl::type::Data* data, vec3 COM, mat4 translation, mat4 rotation){
  if(data == nullptr) return;
  //---------------------------

  mat4 COM_mat = get_translation_mat_neye(COM);

  data->model = translation;
  data->model -= COM_mat;
  data->model *= rotation;
  data->model += COM_mat;

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
