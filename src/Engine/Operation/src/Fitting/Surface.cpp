#include "Surface.h"


namespace ope::fitting{

//Constructor / Destructor
Surface::Surface(){
  //---------------------------


  //---------------------------
}
Surface::~Surface(){}

//Main function
void Surface::compute(vector<vec3>& data){
  Eigen::VectorXf E = Eigen::VectorXf::Zero(data.size());
  this->P = Eigen::VectorXf::Zero(nbP);
  int iter = 10;
  //---------------------------

  Eigen::MatrixXf J = jacobian(data);
  Eigen::MatrixXf J_t = J.transpose();
  Eigen::MatrixXf A = J_t * J;
  Eigen::MatrixXf C = A.inverse();

  for(int i=0; i<iter; i++){
    for(int j=0; j<data.size(); j++){
      float y = data[j].x;
      float x = data[j].y;
      float z = data[j].z;

      //Fitting
      float fit = evaluate(x, y);

      //Error vectors
      E(j) = fit - z;
    }

    //Optimization
    Eigen::VectorXf B = J_t * E;
    this->P = P - C * B;
  }

  //---------------------------
}
float Surface::evaluate(float x, float y){
  //---------------------------

  int cpt = 0;
  float fit = 0;
  for(int i=0; i<=m; i++){
    for(int j=0; j<=n; j++){
      fit += P(cpt) * std::pow(x,i) * std::pow(y,j);
      cpt++;
    }
  }

  //---------------------------
  return fit;
}

//Subfunction
Eigen::MatrixXf Surface::jacobian(vector<vec3>& data){
  Eigen::MatrixXf J = Eigen::MatrixXf::Zero(data.size(), nbP);
  //--------------------------

  for(int k=0; k<R.size(); k++){
    float y = data[k].x;
    float x = data[k].y;

    int cpt = 0;
    for(int i=0; i<=m; i++){
      for(int j=0; j<=n; j++){
        J(k, cpt) = std::pow(x,i) * std::pow(y,j);
        cpt++;
      }
    }
  }

  //---------------------------
  return J;
}


}
