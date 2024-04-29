#include "Surface.h"


namespace ope::fitting{

//Constructor / Destructor
Surface::Surface(){
  //---------------------------

  this->m = 3;
  this->n = 2;
  this->find_number_parameter();

  //---------------------------
}
Surface::~Surface(){}

//Main function
void Surface::compute(vector<vec3>& data){
  Eigen::VectorXf E = Eigen::VectorXf::Zero(data.size());
  this->P = Eigen::VectorXf::Zero(num_param);
  int iter = 10;
  //---------------------------

  Eigen::MatrixXf J = jacobian(data);
  Eigen::MatrixXf J_t = J.transpose();
  Eigen::MatrixXf A = J_t * J;
  Eigen::MatrixXf C = A.inverse();

  for(int i=0; i<iter; i++){
    for(int j=0; j<data.size(); j++){
      float x = data[j].x;
      float y = data[j].y;
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
void Surface::compute(vector<vec3>& data, vec2& x_bound, vec2& y_bound){
  Eigen::VectorXf E = Eigen::VectorXf::Zero(data.size());
  this->P = Eigen::VectorXf::Zero(num_param);
  int iter = 10;
  //---------------------------

  Eigen::MatrixXf J = jacobian(data);
  Eigen::MatrixXf J_t = J.transpose();
  Eigen::MatrixXf A = J_t * J;
  Eigen::MatrixXf C = A.inverse();

  for(int i=0; i<iter; i++){
    for(int j=0; j<data.size(); j++){
      float x = data[j].x;
      float y = data[j].y;
      float z = data[j].z;

      if(x < x_bound[0] || x > x_bound[1]){
        continue;
      }
      if(y < y_bound[0] || y > y_bound[1]){
        continue;
      }

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
  Eigen::MatrixXf J = Eigen::MatrixXf::Zero(data.size(), num_param);
  //--------------------------

  for(int k=0; k<data.size(); k++){
    float x = data[k].x;
    float y = data[k].y;

    int cpt = 0;
    for(int i=0; i<=m; i++){
      for(int j=0; j<=n; j++){
        J(k, cpt) = std::pow(x, i) * std::pow(y, j);
        cpt++;
      }
    }
  }

  //---------------------------
  return J;
}
vector<float> Surface::get_coefficient(){
  std::vector<float> result(P.size());
  //---------------------------

  for(int i=0; i<P.size(); ++i){
    result[i] = static_cast<float>(P[i]);
  }

  //---------------------------
  return result;
}
void Surface::find_number_parameter(){
  this->num_param = 0;
  //-------------------------------

  for(int i=0; i<=m; i++){
    for(int j=0; j<=n; j++){
      num_param++;
    }
  }

  //-------------------------------
}
void Surface::set_coefficients(const std::vector<float>& value){
  //---------------------------

  this->P = Eigen::Map<const Eigen::VectorXf>(value.data(), value.size());

  //---------------------------
}
void Surface::set_degree(int degree_x, int degree_y){
  //---------------------------

  this->m = degree_x;
  this->n = degree_y;
  this->find_number_parameter();

  //---------------------------
}

}