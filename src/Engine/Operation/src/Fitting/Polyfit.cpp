#include "Polyfit.h"


namespace ope::fitting{

//Constructor / Destructor
Polyfit::Polyfit(){
  //---------------------------


  //---------------------------
}
Polyfit::~Polyfit(){}

//Main function
void Polyfit::compute(const std::vector<glm::vec3>& xyz, int degree = 3){
  this->degree = degree;
  //---------------------------

  int numPoints = xyz.size();
  int numParams = (degree + 1) * (degree + 2) / 2;
  Eigen::MatrixXd A;
  Eigen::VectorXd b;

  for(int i = 0; i < numPoints; ++i){
    if(xyz[i] == vec3(-1, -1, -1)){
      continue;
    }

    float x = xyz[i].x;
    float y = xyz[i].y;
    float z = xyz[i].z;

    if(x < 0.5 || x > 4){
      continue;
    }

    Eigen::VectorXd row(numParams);
    int k = 0;
    for (int j = 0; j <= degree; ++j) {
      for (int l = 0; l <= j; ++l) {
        row(k++) = pow(x, j - l) * pow(y, l); // X^i * Y^(j-i)
      }
    }

    if (A.rows() == 0) {
      A.resize(1, numParams);
      b.resize(1);
      A.row(0) = row;
      b(0) = z;
    } else {
      A.conservativeResize(A.rows() + 1, numParams);
      b.conservativeResize(b.size() + 1);
      A.row(A.rows() - 1) = row;
      b(b.size() - 1) = z;
    }
  }

  this->coef = A.colPivHouseholderQr().solve(b); // Solve the system using QR decomposition

  //---------------------------
}
void Polyfit::compute(const std::vector<glm::vec3>& xyz, int degree, vec2 x_bound, vec2 y_bound){
  this->degree = degree;
  //---------------------------

  int numPoints = xyz.size();
  int numParams = (degree + 1) * (degree + 2) / 2;
  Eigen::MatrixXd A;
  Eigen::VectorXd b;

  for(int i = 0; i < numPoints; ++i){
    if(xyz[i] == vec3(-1, -1, -1)){
      continue;
    }

    float x = xyz[i].x;
    float y = xyz[i].y;
    float z = xyz[i].z;

    if(x < x_bound[0] || x > x_bound[1]){
      continue;
    }
    if(y < y_bound[0] || y > y_bound[1]){
      continue;
    }

    Eigen::VectorXd row(numParams);
    int k = 0;
    for (int j = 0; j <= degree; ++j) {
      for (int l = 0; l <= j; ++l) {
        row(k++) = pow(x, j - l) * pow(y, l); // X^i * Y^(j-i)
      }
    }

    if (A.rows() == 0) {
      A.resize(1, numParams);
      b.resize(1);
      A.row(0) = row;
      b(0) = z;
    } else {
      A.conservativeResize(A.rows() + 1, numParams);
      b.conservativeResize(b.size() + 1);
      A.row(A.rows() - 1) = row;
      b(b.size() - 1) = z;
    }
  }

  this->coef = A.colPivHouseholderQr().solve(b); // Solve the system using QR decomposition

  //---------------------------
}
double Polyfit::evaluate(double x, double y){
  if(degree == 0) return -1;
  //---------------------------

  int k = 0;
  double z = 0.0;
  for(int i = 0; i <= degree; ++i){
    for(int j = 0; j <= i; ++j){
      z += coef(k++) * pow(x, i - j) * pow(y, j); // Sum of parameters * X^i * Y^(j-i)
    }
  }

  //---------------------------
  return z;
}

}
