#pragma once

#include <Eigen/Dense>
#include <glm/glm.hpp>
#include <vector>
#include <string>


namespace transtypage{

//EIGEN TO EIGEN
Eigen::Vector4d eigen_4d(Eigen::Vector3d in);

//EIGEN to GLM
glm::mat4 eigen_to_glm_mat4(Eigen::Matrix4f mat_eig);
glm::mat4 eigen_to_glm_mat4(Eigen::Matrix4d mat_eig);
glm::mat4 eigen_to_glm_mat4(Eigen::Matrix3f mat_eig);
glm::mat4 eigen_to_glm_mat4(Eigen::Matrix3d mat_eig);
glm::vec3 eigen_to_glm_vec3(Eigen::Vector3f eig_vec);
glm::vec3 eigen_to_glm_vec3(Eigen::Vector3d eig_vec);
std::vector<glm::vec3> eigen_to_glm_vectorVec3(std::vector<Eigen::Vector3f> eig_vec, int nb_thread);
std::vector<glm::vec3> eigen_to_glm_vectorVec3(std::vector<Eigen::Vector3d> eig_vec, int nb_thread);

//GLM to Eigen
Eigen::MatrixXf glm_to_eigen(const std::vector<glm::vec3>& XYZ);
Eigen::Vector3f glm_to_eigen_vec3(const glm::vec3& vec_glm);
Eigen::Vector4d glm_to_eigen_vec3_4d(const glm::vec3& vec, float scalar);
Eigen::Vector3f glm_to_eigen_mat4_vec3(const glm::mat4& mat_glm);
Eigen::Vector3f glm_to_eigen_mat4_vec3d(const glm::mat4& mat_glm);
Eigen::Matrix4f glm_to_eigen_mat4_mat4f(const glm::mat4& mat_glm);
Eigen::Matrix4d glm_to_eigen_mat4_mat4d(const glm::mat4& mat_glm);
Eigen::Matrix3f glm_to_eigen_mat4_mat3d(const glm::mat4& mat_glm);
Eigen::MatrixXf glm_to_eigen_mat4_matXf(const glm::mat4& mat_glm);

//STD to GLM
glm::mat4 char_to_glm_mat4(char* mat_char);

//Specific
std::vector<float> vec_double_to_float(std::vector<double> vec);
bool string_to_bool(std::string const& s);

}
