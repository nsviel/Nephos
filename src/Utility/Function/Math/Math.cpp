#include "Math.h"

#include <Utility/Function/Math/Distance.h>
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
    Use with for(auto i: math::sort_by_index(v)){
                std::cout << v[i] << std::endl;
              }
  */
  //---------------------------

  // initialize original index locations
  std::vector<size_t> idx(v.size());
  std::iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  std::sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2){return v[i1] < v[i2];});

  //---------------------------
  return idx;
}
std::vector<size_t> sort_by_index_greater(const std::vector<float> &v){
  /*Sorting functions
    --->Sort by order, keeping trace of indices
    Use with for(auto i: math::sort_by_index(v)){
                std::cout << v[i] << std::endl;
              }
  */
  //---------------------------

  // initialize original index locations
  std::vector<size_t> idx(v.size());
  std::iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  std::sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2){return v[i1] > v[i2];});

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
glm::vec3 centroid(const std::vector<glm::vec3>& vec){
  glm::vec3 centroid = glm::vec3(0, 0, 0);
  //---------------------------

  for(int i=0; i<vec.size(); i++){
    for(int j=0; j<3; j++){
      centroid[j] += vec[i][j];
    }
  }

  for(int j=0; j<3; j++){
    centroid[j] /= vec.size();
  }

  //---------------------------
  return centroid;
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
float compute_cosIt(glm::vec3& xyz, glm::vec3& Nxyz, glm::vec3& root){
  //---------------------------

  //Compute cosIt
  float cIt = 0;
  float dist = math::distance(xyz, root);
  for(int j=0; j<3; j++){
    cIt = cIt + ( -Nxyz[j] * ( (xyz[j] - root[j]) / dist ));
  }

  //Check for orientation
  if(cIt < 0){
    cIt = -cIt;
  }
  //Check for computability
  if(cIt >= 1){
    cIt = 0.9999;
  }

  //---------------------------
  return cIt;
}
float compute_It(glm::vec3& xyz, glm::vec3& Nxyz, float& R){
  //---------------------------

  //Compute cosIt
  float cIt = 0;
  glm::vec3 root = glm::vec3(0, 0, 0);
  for(int j=0; j<3; j++){
    cIt = cIt + ( -Nxyz[j] * ( (xyz[j] - root[j]) / R ));
  }

  //Check for orientation
  if(cIt < 0){
    cIt = -cIt;
  }
  //Check for computability
  if(cIt >= 1){
    cIt = 0.9999;
  }

  float It = acos(cIt) * 180 / M_PI;

  //---------------------------
  return It;
}

//Normalization
void normalize(std::vector<float>& vec){
  //-----------------------------

  int size = vec.size();
  if(size == 0) return;

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
    float& value = vec[i];

    if(isnan(value) || value < min || value > max){
      value = -1;
    }else{
      value = (value - min) / (max - min);
    }
  }

  //-----------------------------
}
void normalize(std::vector<float>& vec, glm::vec2 range, glm::vec2 clamp){
  int size = vec.size();
  //-----------------------------

  //Retrieve min & max
  float min = (float)range.x;
  float max = (float)range.y;

  //Normalization
  #pragma omp parallel for
  for(int i=0; i<size; i++){
    float& value = vec[i];

    if(isnan(value) || value < min){
      value = clamp.x;
    }
    else if(value > max){
      value = clamp.y;
    }
    else{
      value = (value - min) / (max - min);
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
void compute_mean_and_std(const std::vector<float>& vec, float& mean, float& std){
  //-----------------------------

  float sum = std::accumulate(vec.begin(), vec.end(), 0.0f);
  mean = sum / vec.size();
  std = 0.0f;
  for(const auto& val : vec){
      std += (val - mean) * (val - mean);
  }
  std = std::sqrt(std / vec.size());

  //-----------------------------
}
std::vector<float> standardize(std::vector<float>& vec, float value_to_avoid){
  std::vector<float> vec_out(vec);
  //-----------------------------

  int size = vec.size();
  if(size == 0) return vec_out;

  // Compute mean and standard deviation
  float mean, std;
  math::compute_mean_and_std(vec, mean, std);

  // Retrieve min & max, and filter out outliers
  float min = std::numeric_limits<float>::max();
  float max = std::numeric_limits<float>::lowest();

  for(auto& val : vec){
    if(val != value_to_avoid){
      if(val > mean + 3 * std || val < mean - 3 * std){
        val = value_to_avoid;
      }else{
        if(val > max) max = val;
        if(val < min) min = val;
      }
    }
  }

  // Normalization
  float range = max - min;
  if(range > 0){
    for(int i = 0; i < size; ++i){
      if(vec[i] != value_to_avoid){
        vec_out[i] = (vec[i] - min) / range;
      }else{
        vec_out[i] = value_to_avoid;
      }
    }
  }

  //-----------------------------
  return vec_out;
}

//Normal
glm::mat3 compute_covariance(const std::vector<glm::vec3>& points){
  //---------------------------

  glm::vec3 centroid(0.0f);
  for(const auto& point : points){
    centroid += point;
  }
  centroid /= static_cast<float>(points.size());

  glm::mat3 covariance(0.0f);
  for(const auto& point : points){
    glm::vec3 deviation = point - centroid;
    covariance += glm::outerProduct(deviation, deviation);
  }
  covariance /= static_cast<float>(points.size());

  //---------------------------
  return covariance;
}
glm::vec3 compute_normal_from_covariance(const glm::mat3& covariance){
  //---------------------------

  // Convert glm::mat3 to Eigen::Matrix3f
  Eigen::Matrix3f eigenCovariance;
  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      eigenCovariance(i, j) = covariance[i][j];
    }
  }

  // Calculate the eigenvalues and eigenvectors of the covariance matrix
  Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eigensolver(eigenCovariance);
  Eigen::Vector3f eigenvalues = eigensolver.eigenvalues();
  Eigen::Matrix3f eigenvectors = eigensolver.eigenvectors();

  // The eigenvector corresponding to the smallest eigenvalue represents the normal
  Eigen::Vector3f normalEigen = eigenvectors.col(0);

  // Convert Eigen::Vector3f to glm::vec3
  glm::vec3 normal(normalEigen[0], normalEigen[1], normalEigen[2]);

  //---------------------------
  return normal;
}
void compute_normal_orientation(glm::vec3& normal, const glm::vec3& point){
  //---------------------------

  // Check orientation towards the origin
  glm::vec3 centroid(0.0f); // Assuming the origin is (0, 0, 0)
  float dotProduct = glm::dot(normal, centroid - point);
  if(dotProduct < 0.0f){
    // Invert the normal
    normal = -normal;
  }

  //---------------------------
}
float calculate_angle(const glm::vec3& v1, const glm::vec3& v2){
  //---------------------------

  // Ensure both vectors are normalized
  glm::vec3 norm_v1 = glm::normalize(v1);
  glm::vec3 norm_v2 = glm::normalize(v2);

  // Calculate the dot product
  float dot_product = glm::dot(norm_v1, norm_v2);

  // Clamp the dot product to avoid numerical errors that might push the value outside [-1, 1]
  dot_product = glm::clamp(dot_product, -1.0f, 1.0f);

  // Calculate the angle in radians using acos
  float angle = acos(dot_product);

  //---------------------------
  return angle;
}

// Function to determine if two vectors are pointing in the same direction
bool normal_same_sense(const glm::vec3& v1, const glm::vec3& v2){
  //---------------------------

  float dot = glm::dot(v1, v2);

  //---------------------------
  return dot > 0;
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
  while(it != s.end() && std::isdigit(*it)) ++it;

  //---------------------------
  return !s.empty() && it == s.end();
}

//Misc
double ceil(double value, int decimalPlaces){
  //---------------------------

  double factor = 1.0;
  for(int i = 0; i < decimalPlaces; ++i){
    factor *= 10.0;
  }
  double ceilValue = std::ceil(value * factor);

  //---------------------------
  return ceilValue / factor;
}
double truncate(double value, int decimalPlaces){
  //---------------------------

  double factor = 1.0;
  for(int i = 0; i < decimalPlaces; ++i){
    factor *= 10.0;
  }
  int truncatedValue = static_cast<int>(value * factor);

  //---------------------------
  return truncatedValue / factor;
}
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
    for(int i = num.size() - 1;
         i >= 0; i--){
        count++;
        ans.push_back(num[i]);

        // If three characters
        // are traversed
        if(count == 3){
            ans.push_back(' ');
            count = 0;
        }
    }

    // Reverse the string to get
    // the desired output
    std::reverse(ans.begin(), ans.end());

    // If the given string is
    // less than 1000
    if(ans.size() % 4 == 0){

        // Remove ','
        ans.erase(ans.begin());
    }

    return ans;
}

}
