#include "Polyfit.h"


namespace ope::fitting{

//Constructor / Destructor
Polyfit::Polyfit(){
  //---------------------------


  //---------------------------
}
Polyfit::~Polyfit(){}

//Main function
void Polyfit::compute(const std::vector<float>& x, const std::vector<float>& y, const std::vector<float>& z, int degree = 3){
  this->degree = degree;
  //---------------------------

  int numPoints = x.size();
  int numParams = (degree + 1) * (degree + 2) / 2; // Number of parameters for polynomial of degree "degree"
  Eigen::MatrixXd A(numPoints, numParams);
  Eigen::VectorXd b(numPoints);

  for (int i = 0; i < numPoints; ++i) {
    int k = 0;
    for (int j = 0; j <= degree; ++j) {
      for (int l = 0; l <= j; ++l) {
        A(i, k++) = pow(x[i], j - l) * pow(y[i], l); // X^i * Y^(j-i)
      }
    }
    b(i) = z[i]; // Z
  }

  this->coef = A.colPivHouseholderQr().solve(b); // Solve the system using QR decomposition

  //---------------------------
}
double Polyfit::evaluate(double x, double y){
  if(degree == 0) return;
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
