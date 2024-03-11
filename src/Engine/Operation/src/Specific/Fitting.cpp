#include "Fitting.h"


//Constructor / Destructor
Fitting::Fitting(){
  //---------------------------

  //---------------------------
}
Fitting::~Fitting(){}

//Sphere fitting
void Fitting::find_sphere(utl::type::Entity* entity, vec3& center, float& radius){
  utl::type::Data* data = entity->get_data();
  utl::type::Pose* pose = entity->get_pose();
  //------------------------

  vector<vec3>& xyz = data->point.xyz;
  vec3& COM = pose->COM;

  // Compute the covariance matrix M of the Y[i] = X[i]-A and the
  // right-hand side R of the linear system M*(C-A) = R.
  float M00 = 0, M01 = 0, M02 = 0, M11 = 0, M12 = 0, M22 = 0;
  vec3 R = {0, 0, 0};
  for (int i=0; i<xyz.size(); i++){
    vec3 Y = xyz[i] - COM;
    float Y0Y0 = Y[0] * Y[0];
    float Y0Y1 = Y[0] * Y[1];
    float Y0Y2 = Y[0] * Y[2];
    float Y1Y1 = Y[1] * Y[1];
    float Y1Y2 = Y[1] * Y[2];
    float Y2Y2 = Y[2] * Y[2];
    M00 += Y0Y0;
    M01 += Y0Y1;
    M02 += Y0Y2;
    M11 += Y1Y1;
    M12 += Y1Y2;
    M22 += Y2Y2;
    R += (Y0Y0 + Y1Y1 + Y2Y2) * Y;
  }
  R *= 0.5;

  // Solve the linear system M*(C-A) = R for the center C.
  float cof00 = M11 * M22 - M12 * M12;
  float cof01 = M02 * M12 - M01 * M22;
  float cof02 = M01 * M12 - M02 * M11;
  float det = M00 * cof00 + M01 * cof01 + M02 * cof02;
  if(det != 0.0f){
    float cof11 = M00 * M22 - M02 * M02;
    float cof12 = M01 * M02 - M00 * M12;
    float cof22 = M00 * M11 - M01 * M01;
    center[0] = COM[0] + (cof00 * R[0] + cof01 * R[1] + cof02 * R[2]) / det;
    center[1] = COM[1] + (cof01 * R[0] + cof11 * R[1] + cof12 * R[2]) / det;
    center[2] = COM[2] + (cof02 * R[0] + cof12 * R[1] + cof22 * R[2]) / det;

    float rsqr = 0.0f;
    for (int i=0; i<xyz.size(); i++){
      vec3 delta = xyz[i] - center;
      rsqr += math::dot_product(delta, delta);
    }
    rsqr *= (1/xyz.size());
    radius = std::sqrt(rsqr);
  }
  else{
     center = {0, 0, 0};
     radius = 0;
  }

  //------------------------
}
