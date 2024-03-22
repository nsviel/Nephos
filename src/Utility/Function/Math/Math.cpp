#include "Math.h"

#include <random>


namespace math{

//Operation
void divise(std::vector<float>& vec, int diviser){
  //---------------------------

  int size = vec.size();
  #pragma omp parallel for
  for(int i=0; i<size; i++){
    vec[i] /= diviser;
  }

  //---------------------------
}
std::vector<size_t> sort_by_index(const std::vector<float> &v){
  /*Sorting functions
    --->Sort by order, keeping trace of indices
    Use with for (auto i: math::sort_by_index(v)) {
                cout << v[i] << endl;
              }
  */
  //---------------------------

  // initialize original index locations
  std::vector<size_t> idx(v.size());
  std::iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  std::sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

  //---------------------------
  return idx;
}
std::vector<size_t> sort_by_index_greater(const std::vector<float> &v){
  /*Sorting functions
    --->Sort by order, keeping trace of indices
    Use with for (auto i: math::sort_by_index(v)) {
                cout << v[i] << endl;
              }
  */
  //---------------------------

  // initialize original index locations
  std::vector<size_t> idx(v.size());
  std::iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  std::sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {return v[i1] > v[i2];});

  //---------------------------
  return idx;
}
std::vector<float> inv(std::vector<float>& vec){
  //Vector inversion
  std::vector<float> vec_out;
  int size = vec.size();
  //---------------------------

  for(int i=0; i<size; i++){
    vec_out.push_back(vec[size-1-i]);
  }

  //---------------------------
  return vec_out;
}

//Normalization
void normalize(std::vector<float>& vec){
  int size = vec.size();
  //-----------------------------

  //Retrieve min & max
  float min = vec[0];
  float max = vec[0];
  for(int i=0; i<size; i++){
    if(vec[i] > max) max = vec[i];
    if(vec[i] < min) min = vec[i];
  }

  //Normalization
  #pragma omp parallel for
  for(int i=0; i<size; i++){
    vec[i] = (vec[i] - min) / (max - min);
  }

  //-----------------------------
}
void normalize(std::vector<float>& vec, glm::vec2 range){
  int size = vec.size();
  //-----------------------------

  //Retrieve min & max
  float min = (float)range.x;
  float max = (float)range.y;

  //Normalization
  #pragma omp parallel for
  for(int i=0; i<size; i++){
    if(vec[i] < min || vec[i] > max){
      vec[i] = -1;
    }else{
      vec[i] = (vec[i] - min) / (max - min);
    }
  }

  //-----------------------------
}
void normalize(std::vector<float>& vec, float value_to_avoid){
  int size = vec.size();
  //-----------------------------

  //Retrieve min & max
  float min = vec[0];
  float max = vec[0];
  for(int i=0; i<size; i++){
    if(vec[i] != value_to_avoid){
      if(vec[i] > max) max = vec[i];
      else if(vec[i] < min) min = vec[i];
    }
  }

  //Normalization
  #pragma omp parallel for
  for(int i=0; i<size; i++){
    if(vec[i] != value_to_avoid){
      vec[i] = (vec[i] - min) / (max - min);
    }
  }

  //-----------------------------
}
std::vector<float> standardize(std::vector<float>& vec, float value_to_avoid){
  std::vector<float> vec_out(vec);
  int size = vec.size();
  //-----------------------------

  //Compute std
  float sum = 0.0, mean, std = 0.0;
  for(int i=0; i<vec.size(); i++){
    sum += vec[i];
  }
  mean = sum/vec.size();
  for(int i=0; i<vec.size(); i++){
    std += pow(vec[i] - mean, 2);
  }
  std = sqrt(std / vec.size());

  //Retrieve min & max
  float min = vec[0];
  float max = vec[0];
  for(int i=0; i<size; i++){
    if(vec[i] != value_to_avoid){
      if(vec[i] > mean + std * 3 || vec[i] < mean - std * 3) vec[i] = value_to_avoid;
      else if(vec[i] > max && vec[i] != value_to_avoid) max = vec[i];
      else if(vec[i] < min && vec[i] != value_to_avoid) min = vec[i];
    }
  }

  //Normalization
  for(int i=0; i<size; i++){
    if(vec[i] != value_to_avoid && vec[i] < mean + std * 3){
      vec_out[i] = (vec[i] - min) / (max - min);
    }else{
      vec_out[i] = vec[i];
    }
  }

  //-----------------------------
  return vec_out;
}

//Conversion
float degree_to_radian(float degree){
  float radian;
  //---------------------------

  radian = degree * 3.14159265358979323846f / 180;

  //---------------------------
  return radian;
}
float radian_to_degree(float radian){
  float degree;
  //---------------------------

  degree = (radian * 180) / 3.14159265358979323846f;

  //---------------------------
  return degree;
}
glm::vec3 degree_to_radian(glm::vec3 degree){
  glm::vec3 radian;
  //---------------------------

  for(int i=0; i<3; i++){
    radian[i] = degree[i] * 3.14159265358979323846f / 180;
  }

  //---------------------------
  return radian;
}
glm::vec3 radian_to_degree_vec3(glm::vec3 radian){
  glm::vec3 degree;
  //---------------------------

  for(int i=0; i<3; i++){
    degree[i] = (radian[i] * 180) / 3.14159265358979323846f;
  }

  //---------------------------
  return degree;
}

//Checker
bool is_nan(glm::vec3 vec){
  //---------------------------

  if(isnan(vec[0]) || isnan(vec[1]) || isnan(vec[2])){
    return true;
  }

  //---------------------------
  return false;
}
bool is_nan(Eigen::Vector3d vec){
  //---------------------------

  if(isnan(vec(0)) || isnan(vec(1)) || isnan(vec(2))){
    return true;
  }

  //---------------------------
  return false;
}
bool is_number(const std::string& s){
  //---------------------------

  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;

  //---------------------------
  return !s.empty() && it == s.end();
}

//Misc
float sign(float value){
  //---------------------------

  if(std::signbit(value)){
    return -1;
  }else{
    return 1;
  }

  //---------------------------
}
glm::vec4 random(){
  //---------------------------

  srand(static_cast<unsigned>(8));
  float R = float(rand()) / RAND_MAX;
  float G = float(rand()) / RAND_MAX;
  float B = float(rand()) / RAND_MAX;
  glm::vec4 color = glm::vec4(R, G, B, 1.0f);

  //---------------------------
  return color;
}
glm::vec4 random(int seed){
  //---------------------------

  //Assign a specific random color
  std::mt19937 rng(seed);

  // Generate random values for R, G, and B channels
  std::uniform_real_distribution<double> dist(0.0f, 1.0f);
  float r = dist(rng);
  float g = dist(rng);
  float b = dist(rng);
  glm::vec4 color = glm::vec4(r, g, b, 1);

  //---------------------------
  return color;
}
std::string thousand_separator(int n){
    std::string ans = "";

    // Convert the given integer
    // to equivalent string
    std::string num = std::to_string(n);

    // Initialise count
    int count = 0;

    // Traverse the string in reverse
    for (int i = num.size() - 1;
         i >= 0; i--) {
        count++;
        ans.push_back(num[i]);

        // If three characters
        // are traversed
        if (count == 3) {
            ans.push_back(' ');
            count = 0;
        }
    }

    // Reverse the string to get
    // the desired output
    std::reverse(ans.begin(), ans.end());

    // If the given string is
    // less than 1000
    if (ans.size() % 4 == 0) {

        // Remove ','
        ans.erase(ans.begin());
    }

    return ans;
}

}
