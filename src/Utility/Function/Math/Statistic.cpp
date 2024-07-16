#include "truc.h"

#include <random>


namespace math{

Eigen::Matrix3f covariance(std::vector<Eigen::Vector3f>& vec){
  //---------------------------

  // Centroide
  Eigen::Vector3f centroid = math::centroid(vec);

  //Covariance matrix
  Eigen::Matrix3f covMat = Eigen::Matrix3f::Zero();
  for(int i=0; i<vec.size(); i++){
    for(int j=0; j<3; j++){
      for(int k=j; k<3; k++){
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

    for(int j=0; j<3; ++j){
      for(int k=j; k<3; ++k){
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
