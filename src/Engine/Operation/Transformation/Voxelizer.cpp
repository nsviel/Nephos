#include "Voxelizer.h"

#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
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
void Voxelizer::find_voxel_min_number_of_point(utl::base::Data* data){
  voxel_map.clear();
  //---------------------------

  //Insert point and index into voxel map
  int cpt = 0;
  #pragma omp parallel for
	for(const glm::vec3& point : data->xyz){
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
        glm::vec4 point = voxel[i];
        vec_goodness[point.w] = false;
      }

		}
	}

  //---------------------------
}
void Voxelizer::find_voxel_min_number_of_point(utl::base::Data* data, float voxel_size, int min_nb_point){
  voxel_map.clear();
  //---------------------------

  //Insert point and index into voxel map
  #pragma omp parallel for
	for(int i=0; i<data->xyz.size(); i++){
    int kx = static_cast<int>(data->xyz[i].x / voxel_size);
    int ky = static_cast<int>(data->xyz[i].y / voxel_size);
    int kz = static_cast<int>(data->xyz[i].z / voxel_size);
    int kw = i;
    int key = (kx*2000 + ky)*1000 + kz;
    glm::vec4 point = glm::vec4(data->xyz[i].x, data->xyz[i].y, data->xyz[i].z, i);
    voxel_map[key].push_back(point);
	}

  for(auto it = voxel_map.begin(); it != voxel_map.end(); it++){
    //If no enough point in voxel, disabled them all
		if(it->second.size() < min_nb_point){

      Voxel voxel = it->second;
      for(int i=0; i<voxel.size(); i++){
        glm::vec4 point = voxel[i];
        vec_goodness[point.w] = false;
      }

		}
	}

  //---------------------------
}
void Voxelizer::reconstruct_data_by_goodness(utl::base::Data* data){
  //---------------------------

  // Use std::remove_if to move the unwanted elements to the end
  auto newEnd = std::remove_if(vec_goodness.begin(), vec_goodness.end(), [](bool g){ return !g; });

  // Erase the unwanted elements from the vectors using erase-remove idiom
  data->xyz.erase(std::remove_if(data->xyz.begin(), data->xyz.end(), [&](const auto& val){ return !vec_goodness[&val - &data->xyz[0]]; }), data->xyz.end());
  data->rgb.erase(std::remove_if(data->rgb.begin(), data->rgb.end(), [&](const auto& val){ return !vec_goodness[&val - &data->rgb[0]]; }), data->rgb.end());
  data->R.erase(std::remove_if(data->R.begin(), data->R.end(), [&](const auto& val){ return !vec_goodness[&val - &data->R[0]]; }), data->R.end());
  data->Is.erase(std::remove_if(data->Is.begin(), data->Is.end(), [&](const auto& val){ return !vec_goodness[&val - &data->Is[0]]; }), data->Is.end());

  // Update the nb_point
  data->size = data->xyz.size();

  /*
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec4> rgb;
  std::vector<float> R;
  std::vector<float> Is;

  xyz.reserve(data->xyz.size());
  rgb.reserve(data->xyz.size());
  R.reserve(data->xyz.size());
  Is.reserve(data->xyz.size());

  for(int i=0; i<data->xyz.size(); i++){
    if(vec_goodness[i] == true){
      xyz.push_back(data->xyz[i]);
      rgb.push_back(data->rgb[i]);
      R.push_back(data->R[i]);
      Is.push_back(data->Is[i]);
    }
  }

  data->xyz = xyz;
  data->rgb = rgb;
  data->R = R;
  data->Is = Is;
  data->size = xyz.size();
  */

  //---------------------------
}


}
