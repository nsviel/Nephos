#include "Transformation.h"

#include <Utility/Namespace.h>
#include <glm/gtc/matrix_transform.hpp>


namespace eng::trf{

// Constructor / Destructor
Transformation::Transformation(){
  //---------------------------

  this->trf_utils = new eng::trf::Utils();

  //---------------------------
}
Transformation::~Transformation(){}

// Translation
void Transformation::make_translation(utl::base::Pose* pose, glm::vec3 trans){
  if(!pose->is_movable) return;
  //---------------------------

  glm::mat4 translation = trf_utils->get_translation_mat(trans);

  pose->COM += trans;
  pose->root += trans;
  pose->trans *= translation;
  pose->model *= translation;

  //---------------------------
}
void Transformation::make_translation(utl::base::Pose* pose, glm::mat4 translation){
  if(!pose->is_movable) return;
  //---------------------------

  glm::vec3 trans = glm::vec3(translation[0][3], translation[1][3], translation[2][3]);

  pose->COM += trans;
  pose->root += trans;
  pose->trans *= translation;
  pose->model *= translation;

  //---------------------------
}

//Rotation
void Transformation::make_rotation(utl::base::Pose* pose, glm::vec3 COM, glm::vec3 degree){
  if(!pose->is_movable) return;
  //---------------------------

  glm::vec3 radian = type::degree_to_radian(degree);
  glm::mat4 rotation = trf_utils->get_rotation_mat(radian);
  glm::mat4 COM_mat = trf_utils->get_translation_mat_neye(COM);
  glm::mat4 root_mat = trf_utils->get_translation_mat_neye(pose->root);

  pose->rotat *= rotation;

  //Rotation around COM
  pose->model -= COM_mat;
  pose->model *= rotation;
  pose->model += COM_mat;

  // Apply rotation to the root
  pose->root = glm::mat3(rotation) * (pose->root - COM) + COM;

  //---------------------------
}
void Transformation::make_rotation(utl::base::Pose* pose, glm::vec3 degree){
  if(!pose->is_movable) return;
  //---------------------------

  glm::vec3& COM = pose->COM;
  glm::vec3 radian = type::degree_to_radian(degree);
  glm::mat4 rotation = trf_utils->get_rotation_mat(radian);
  glm::mat4 COM_mat = trf_utils->get_translation_mat_neye(COM);

  pose->rotat *= rotation;

  //Rotation around COM
  pose->model -= COM_mat;
  pose->model *= rotation;
  pose->model += COM_mat;

  // Apply rotation to the root
  pose->root = glm::mat3(rotation) * (pose->root - COM) + COM;

  //---------------------------
}
void Transformation::make_rotation(utl::base::Pose* pose, glm::vec3 COM, glm::mat4 rotation){
  if(!pose->is_movable) return;
  //---------------------------

  //glm::vec3& COM = pose->COM;
  glm::mat4 COM_mat = trf_utils->get_translation_mat_neye(COM);

  pose->rotat *= rotation;

  //Rotation around COM
  pose->model -= COM_mat;
  pose->model *= rotation;
  pose->model += COM_mat;

  // Apply rotation to the root
  pose->root = glm::mat3(rotation) * (pose->root - COM) + COM;

  //---------------------------
}
void Transformation::make_rotation_axe_X(utl::base::Pose* pose, float degree){
  if(!pose->is_movable) return;
  //---------------------------

  float radian = type::degree_to_radian(degree);

  // Matrice de rotation locale autour de l'axe x
  glm::mat4 rotationMatrixXLocal = glm::rotate(glm::mat4(1.0f), radian, glm::vec3(1.0f, 0.0f, 0.0f));

  // Obtenez la partie de translation de la matrice modèle actuelle
  glm::vec3 translation = glm::vec3(pose->model[3]);

  // Appliquez la nouvelle rotation locale à la matrice modèle
  pose->model = glm::translate(glm::mat4(1.0f), translation) * rotationMatrixXLocal * pose->model;

  // Mettez à jour les composantes de rotation cumulatives
  pose->rotat = rotationMatrixXLocal * pose->rotat;

  // Mettez à jour les composantes de translation cumulatives
  pose->trans = glm::translate(glm::mat4(1.0f), translation) * pose->trans;

  //---------------------------
}

//Scaling
void Transformation::make_scaling(utl::base::Pose* pose, float scale){
  if(!pose->is_movable) return;
  //---------------------------

  glm::mat4 scaling(1.0);
  scaling[0][0] = scale;
  scaling[1][1] = scale;
  scaling[2][2] = scale;

  pose->scale *= scaling;
  pose->model *= scaling;

  //---------------------------
}

//Transformation
void Transformation::make_transformation(utl::base::Pose* pose, glm::vec3 COM, glm::mat4 translation, glm::mat4 rotation){
  //---------------------------

  glm::mat4 COM_mat = trf_utils->get_translation_mat_neye(COM);

  pose->model = translation;
  pose->model -= COM_mat;
  pose->model *= rotation;
  pose->model += COM_mat;

  //---------------------------
}

}
