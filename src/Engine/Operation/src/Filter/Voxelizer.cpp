#include "Voxelizer.h"


namespace eng::ope{

// Constructor / Destructor
Voxelizer::Voxelizer(){
  //---------------------------

  this->voxel_size = 0.25;
  this->min_nb_point = 100;

  //---------------------------
}
Voxelizer::~Voxelizer(){}

//Main function
void Voxelizer::find_voxel_min_number_of_point(utl::type::Data* data){
  voxel_map.clear();
  //---------------------------

  //Insert point and index into voxel map
	for(int i=0; i<data->xyz.size(); i++){
    int kx = static_cast<int>(data->xyz[i].x / voxel_size);
    int ky = static_cast<int>(data->xyz[i].y / voxel_size);
    int kz = static_cast<int>(data->xyz[i].z / voxel_size);
    int kw = i;
    int key = (kx*2000 + ky)*1000 + kz;
    vec4 point = vec4(data->xyz[i].x, data->xyz[i].y, data->xyz[i].z, i);
    voxel_map[key].push_back(point);
	}

  //Check if number of point is good and set goodness accordingly
  for(auto it = voxel_map.begin(); it != voxel_map.end(); it++){
		if(it->second.size() < min_nb_point){

      Voxel voxel = it->second;
      for(int i=0; i<voxel.size(); i++){
        vec4 point = voxel[i];
        data->goodness[point.w] = false;
      }

		}
	}

  //---------------------------
}
void Voxelizer::find_voxel_min_number_of_point(utl::type::Data* data, float voxel_size, int min_nb_point){
  voxel_map.clear();
  //---------------------------

  //Insert point and index into voxel map
	for(int i=0; i<data->xyz.size(); i++){
    int kx = static_cast<int>(data->xyz[i].x / voxel_size);
    int ky = static_cast<int>(data->xyz[i].y / voxel_size);
    int kz = static_cast<int>(data->xyz[i].z / voxel_size);
    int kw = i;
    int key = (kx*2000 + ky)*1000 + kz;
    vec4 point = vec4(data->xyz[i].x, data->xyz[i].y, data->xyz[i].z, i);
    voxel_map[key].push_back(point);
	}

  //Check if number of point is good and set goodness accordingly
  for(auto it = voxel_map.begin(); it != voxel_map.end(); it++){
		if(it->second.size() < min_nb_point){

      Voxel voxel = it->second;
      for(int i=0; i<voxel.size(); i++){
        vec4 point = voxel[i];
        data->goodness[point.w] = false;
      }

		}
	}

  //---------------------------
}
void Voxelizer::reconstruct_data_by_goodness(utl::type::Data* data){
  //---------------------------

  std::vector<glm::vec3> xyz;
  std::vector<glm::vec4> rgb;
  std::vector<float> R;
  std::vector<float> Is;

  for(int i=0; i<data->xyz.size(); i++){
    if(data->goodness[i] == true){
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
  data->nb_point = xyz.size();

  //---------------------------
}


}
