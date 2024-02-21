#include "Voxelizer.h"

#include <Engine/Operation/Namespace.h>
#include <cstdlib>


namespace ope{

// Constructor / Destructor
Voxelizer::Voxelizer(){
  //---------------------------

  this->voxel_size = 0.25;
  this->min_nb_point = 100;
  this->max_nb_point = 300;

  //---------------------------
}
Voxelizer::~Voxelizer(){}

//Main function
void Voxelizer::find_voxel_min_number_of_point(utl::type::Data* data){
  voxel_map.clear();
  //---------------------------

  //Insert point and index into voxel map
  int cpt = 0;
  #pragma omp parallel for
	for(const vec3& point : data->point.xyz){
    int kx = static_cast<int>(point.x / voxel_size);
    int ky = static_cast<int>(point.y / voxel_size);
    int kz = static_cast<int>(point.z / voxel_size);
    int kw = cpt++;
    int key = (kx*2000 + ky)*1000 + kz;
    voxel_map[key].emplace_back(point, cpt);
	}

  #pragma omp parallel for
  for(auto it = voxel_map.begin(); it != voxel_map.end(); it++){
    //If no enough point in voxel, disabled them all
    size_t voxel_size = it->second.size();
		if(voxel_size < min_nb_point){

      const Voxel& voxel = it->second;
      #pragma omp parallel for
      for(int i=0; i<voxel_size; i++){
        vec4 point = voxel[i];
        data->point.goodness[point.w] = false;
      }

		}
	}

  //---------------------------
}
void Voxelizer::find_voxel_min_number_of_point(utl::type::Data* data, float voxel_size, int min_nb_point){
  voxel_map.clear();
  //---------------------------

  //Insert point and index into voxel map
  #pragma omp parallel for
	for(int i=0; i<data->point.xyz.size(); i++){
    int kx = static_cast<int>(data->point.xyz[i].x / voxel_size);
    int ky = static_cast<int>(data->point.xyz[i].y / voxel_size);
    int kz = static_cast<int>(data->point.xyz[i].z / voxel_size);
    int kw = i;
    int key = (kx*2000 + ky)*1000 + kz;
    vec4 point = vec4(data->point.xyz[i].x, data->point.xyz[i].y, data->point.xyz[i].z, i);
    voxel_map[key].push_back(point);
	}

  for(auto it = voxel_map.begin(); it != voxel_map.end(); it++){
    //If no enough point in voxel, disabled them all
		if(it->second.size() < min_nb_point){

      Voxel voxel = it->second;
      for(int i=0; i<voxel.size(); i++){
        vec4 point = voxel[i];
        data->point.goodness[point.w] = false;
      }

		}
	}

  //---------------------------
}
void Voxelizer::reconstruct_data_by_goodness(utl::type::Data* data){
  //---------------------------

  // Use std::remove_if to move the unwanted elements to the end
  auto newEnd = std::remove_if(data->point.goodness.begin(), data->point.goodness.end(), [](bool g) { return !g; });

  // Erase the unwanted elements from the vectors using erase-remove idiom
  data->point.xyz.erase(std::remove_if(data->point.xyz.begin(), data->point.xyz.end(), [&](const auto& val) { return !data->point.goodness[&val - &data->point.xyz[0]]; }), data->point.xyz.end());
  data->point.rgb.erase(std::remove_if(data->point.rgb.begin(), data->point.rgb.end(), [&](const auto& val) { return !data->point.goodness[&val - &data->point.rgb[0]]; }), data->point.rgb.end());
  data->point.R.erase(std::remove_if(data->point.R.begin(), data->point.R.end(), [&](const auto& val) { return !data->point.goodness[&val - &data->point.R[0]]; }), data->point.R.end());
  data->point.Is.erase(std::remove_if(data->point.Is.begin(), data->point.Is.end(), [&](const auto& val) { return !data->point.goodness[&val - &data->point.Is[0]]; }), data->point.Is.end());

  // Update the nb_point
  data->point.size = data->point.xyz.size();

  /*
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec4> rgb;
  std::vector<float> R;
  std::vector<float> Is;

  xyz.reserve(data->point.xyz.size());
  rgb.reserve(data->point.xyz.size());
  R.reserve(data->point.xyz.size());
  Is.reserve(data->point.xyz.size());

  for(int i=0; i<data->point.xyz.size(); i++){
    if(data->point.goodness[i] == true){
      xyz.push_back(data->point.xyz[i]);
      rgb.push_back(data->point.rgb[i]);
      R.push_back(data->point.R[i]);
      Is.push_back(data->point.Is[i]);
    }
  }

  data->point.xyz = xyz;
  data->point.rgb = rgb;
  data->point.R = R;
  data->point.Is = Is;
  data->point.size = xyz.size();
  */

  //---------------------------
}


}
