#include "Polyfit.h"


namespace ope::fitting{

//Constructor / Destructor
Polyfit::Polyfit(){
  //---------------------------


  //---------------------------
}
Polyfit::~Polyfit(){}

//Main function
Eigen::VectorXd Polyfit::compute(const Eigen::MatrixXd& data, int degree){
  //---------------------------

  int numPoints = data.rows();
  int numParams = (degree + 1) * (degree + 2) / 2; // Number of parameters for polynomial of degree "degree"
  Eigen::MatrixXd A(numPoints, numParams);
  Eigen::VectorXd b(numPoints);

  for(int i = 0; i < numPoints; ++i){
    int k = 0;
    for(int j = 0; j <= degree; ++j){
      for(int l = 0; l <= j; ++l){
        A(i, k++) = pow(data(i, 0), j - l) * pow(data(i, 1), l); // X^i * Y^(j-i)
      }
    }
    b(i) = data(i, 2); // Z
  }

  //---------------------------
  return A.colPivHouseholderQr().solve(b); // Solve the system using QR decomposition
}
double Polyfit::evaluate(const Eigen::VectorXd& params, double x, double y, int degree){
  //---------------------------

  int k = 0;
  double z = 0.0;
  for(int i = 0; i <= degree; ++i){
    for(int j = 0; j <= i; ++j){
      z += params(k++) * pow(x, i - j) * pow(y, j); // Sum of parameters * X^i * Y^(j-i)
    }
  }

  //---------------------------
  return z;
}

}
