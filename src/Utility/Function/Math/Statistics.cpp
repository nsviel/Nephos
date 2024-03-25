#include "Statistics.h"

#include <random>


namespace math{

float mean(std::vector<float>& vec){
  int size = vec.size();
  float sum = 0;
  //---------------------------

  for(int i=0; i<size; i++){
    sum += vec[i];
  }
  float mean = sum / size;

  //---------------------------
  return mean;
}

int min(std::vector<int>& vec){
  int min = vec[0];
  int size = vec.size();
  //---------------------------

  for(int i=0; i<size; i++){
    if(min > vec[i]) min = vec[i];
  }

  //---------------------------
  return min;
}
float min(std::vector<float>& vec){
  float min = vec[0];
  int size = vec.size();
  //---------------------------

  for(int i=0; i<size; i++){
    if(min > vec[i]) min = vec[i];
  }

  //---------------------------
  return min;
}
float min(float in1, float in2){
  //---------------------------

  if(in1 > in2){
    return in2;
  }else{
    return in1;
  }

  //---------------------------
}
glm::vec2 min(std::vector<glm::vec2> XY){
  glm::vec2 min = XY[0];
  int size = XY.size();
  //---------------------------

  for(int i=0; i<size; i++){
    for(int j=0; j<2; j++){
      if(XY[i][j] <= min[j]) min[j] = XY[i][j];
    }
  }

  //---------------------------
  return min;
}
glm::vec3 min(std::vector<glm::vec3> XYZ){
  glm::vec3 min = glm::vec3(100000000.0f);
  int size = XYZ.size();
  //---------------------------

  for(int i=0; i<size; i++){
    for(int j=0; j<3; j++){
      if ( XYZ[i][j] <= min[j] ) min[j] = XYZ[i][j];
    }
  }

  //---------------------------
  return min;
}

float max(std::vector<float>& vec){
  int size = vec.size();
  if(size == 0) return 0;
  //---------------------------

  float max = vec[0];
  for(int i=0; i<size; i++){
    if(max < vec[i]) max = vec[i];
  }

  //---------------------------
  return max;
}
float max(std::vector<std::vector<float>>& vec){
  float max = vec[0].size();
  int size = vec.size();
  //---------------------------

  for(int i=0; i<size; i++){
    if(max < vec[i].size()) max = vec[i].size();
  }

  //---------------------------
  return max;
}
glm::vec2 max(std::vector<glm::vec2> XY){
  glm::vec2 max = XY[0];
  int size = XY.size();
  //---------------------------

  for(int i=0; i<size; i++){
    for(int j=0; j<2; j++){
      if(XY[i][j] >= max[j]) max[j] = XY[i][j];
    }
  }

  //---------------------------
  return max;
}
glm::vec3 max(std::vector<glm::vec3> XYZ){
  glm::vec3 max = XYZ[0];
  int size = XYZ.size();
  //---------------------------

  for(int i=0; i<size; i++){
    for(int j=0; j<3; j++){
      if(XYZ[i][j] >= max[j]) max[j] = XYZ[i][j];
    }
  }

  //---------------------------
  return max;
}

float sum(std::vector<float>& vec){
  //Sum of vector elements
  float out = 0;
  int size = vec.size();
  //---------------------------

  for(int i=0; i<size; i++){
    out = out + vec[i];
  }

  //---------------------------
  return out;
}
float dot_product(glm::vec3& vec_A, glm::vec3& vec_B){
  float product = 0;
  //---------------------------

  // Loop for calculate cot product
  for(int i=0; i<3; i++){
    product = product + vec_A[i] * vec_B[i];
  }

  //---------------------------
  return product;
}
float oriented_angle(glm::vec2 A, glm::vec2 B){
  //---------------------------

  float det = A.x * B.y - A.y * B.x;
  float dot = A.x * B.x + A.y * B.y;
  float angle = atan2(det, dot);

  //---------------------------
  return angle;
}
double angular_distance(const Eigen::Matrix3f &rota, const Eigen::Matrix3f &rotb){
  //---------------------------

  double norm = ((rota * rotb.transpose()).trace() - 1) / 2;
  norm = std::acos(norm) * 180 / M_PI;

  //---------------------------
  return norm;
}
std::vector<float> cross_product(std::vector<float>& vec_A, std::vector<float>& vec_B){
  std::vector<float> vec_cross;
  //---------------------------

  vec_cross[0] = vec_A[1] * vec_B[2] - vec_A[2] * vec_B[1];
  vec_cross[1] = vec_A[2] * vec_B[0] - vec_A[0] * vec_B[2];
  vec_cross[2] = vec_A[0] * vec_B[1] - vec_A[1] * vec_B[0];

  //---------------------------
  return vec_cross;
}

glm::vec3 centroid(std::vector<glm::vec3>& vec){
  glm::vec3 centroid = glm::vec3(0, 0, 0);
  //---------------------------

  for(int i=0; i<vec.size(); i++){
    for(int j=0; j<3; j++){
      centroid[j] += vec[i][j];
    }
  }

  for(int j=0;j<3;j++){
    centroid[j] /= vec.size();
  }

  //---------------------------
  return centroid;
}
glm::vec3 centroid(glm::vec3& vec1, glm::vec3& vec2){
  glm::vec3 centroid = glm::vec3(0, 0, 0);
  //---------------------------

  centroid.x = (vec1.x + vec2.x) / 2;
  centroid.y = (vec1.y + vec2.y) / 2;
  centroid.z = (vec1.z + vec2.z) / 2;

  //---------------------------
  return centroid;
}
Eigen::Vector3f centroid(std::vector<Eigen::Vector3f>& XYZ){
  Eigen::Vector3f centroid = Eigen::Vector3f::Zero();
  int size = XYZ.size();
  //---------------------------

  for(int i=0; i<size; i++){
    for(int j=0; j<3; j++){
      centroid(j) += XYZ[i](j);
    }
  }

  for(int i=0; i<3; i++){
    centroid(i) /= size;
  }

  //---------------------------
  return centroid;
}
Eigen::Vector3d centroid(std::vector<Eigen::Vector3d>& XYZ){
  Eigen::Vector3d centroid = Eigen::Vector3d::Zero();
  int size = XYZ.size();
  //---------------------------

  for(int i=0; i<size; i++){
    for(int j=0; j<3; j++){
      centroid(j) += XYZ[i](j);
    }
  }

  for(int i=0; i<3; i++){
    centroid(i) /= (double) size;
  }

  //---------------------------
  return centroid;
}
Eigen::Matrix3f covariance(std::vector<Eigen::Vector3f>& vec){
  //---------------------------

  // Centroide
  Eigen::Vector3f centroid = math::centroid(vec);

  //Covariance matrix
  Eigen::Matrix3f covMat = Eigen::Matrix3f::Zero();
  for(int i=0; i<vec.size(); i++){
    for (int j=0; j<3; j++){
      for (int k=j; k<3; k++){
        Eigen::Vector3f point = vec[i];
        covMat(j, k) += (point(j) - centroid(j)) * (point(k) - centroid(k));
      }
    }
  }
  covMat(1, 0) = covMat(0, 1);
  covMat(2, 0) = covMat(0, 2);
  covMat(2, 1) = covMat(1, 2);

  //---------------------------
  return covMat;
}
Eigen::Matrix3d covariance(std::vector<Eigen::Vector3d>& vec){
  //---------------------------

  // Centroide
  Eigen::Vector3d centroid = math::centroid(vec);

  //Covariance matrix
  Eigen::Matrix3d covMat = Eigen::Matrix3d::Zero();
  for(int i=0; i<vec.size(); i++){
    Eigen::Vector3d point = vec[i];

    for (int j=0; j<3; ++j){
      for (int k=j; k<3; ++k){
        covMat(j, k) += (point(j) - centroid(j)) * (point(k) - centroid(k));
      }
    }
  }
  covMat(1, 0) = covMat(0, 1);
  covMat(2, 0) = covMat(0, 2);
  covMat(2, 1) = covMat(1, 2);

  //---------------------------
  return covMat;
}

float std(std::vector<float>& vec){
  // Standard deviation
  float sum = 0.0, mean, Std = 0.0;
  int size = vec.size();
  //-------------------

  for(int i=0; i<size; i++){
    sum += vec[i];
  }

  mean = sum/size;
  for(int i=0; i<size; i++){
    Std += pow(vec[i] - mean, 2);
  }

  //-------------------
  return sqrt(Std / vec.size());
}
float var(std::vector<float>& vec){
  int size = vec.size();
  //---------------------------

  //Mean
  float sum = 0.0, mean;
  for(int i=0; i<size; i++){
    sum += vec[i];
  }
  mean = sum/size;

  //Variance
  float var = 0.0;
  for(int i=0; i<size; i++){
    var += pow(vec[i] - mean, 2);
  }
  var = var / size;

  //---------------------------
  return var;
}
float cv(std::vector<float>& vec){
  //Coefficient of variation
  //---------------------------

  float std = math::std(vec);
  float CV = (std / mean(vec)) * 100;

  //---------------------------
  return CV;
}
float R2(std::vector<float>& data_X, std::vector<float>& data_Y, std::vector<float>& coeffs){
  int size = data_Y.size();
  float up = 0.0f, bot = 0.0f, R_2;
  //---------------------------

  for(int i=0; i<size; i++){
    if(coeffs.size() == 2) up += pow((data_Y[i] - (coeffs[1]*data_X[i] + coeffs[0])), 2);
    if(coeffs.size() == 3) up += pow((data_Y[i] - (coeffs[2]*pow(data_X[i],2) + coeffs[1]*data_X[i] + coeffs[0])), 2);
    bot += pow((data_Y[i] - mean(data_Y)), 2);
  }
  R_2 = 1 - (up / bot);
  std::cout<<"---> R² = "<<R_2<<std::endl;

  //---------------------------
  return R_2;
}


}
