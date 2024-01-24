#include "Voxel.h"


namespace eng::ope{

// Constructor / Destructor
Voxel::Voxel(){
  //---------------------------


  //---------------------------
}
Voxel::~Voxel(){}

//Main function
void Voxel::sub_sampling_subset(utl::type::Data* data){
  vector<vec3> xyz_sampled;
  float size_voxel = 0.2;
  //---------------------------
/*
  cloudMap grid;
  Eigen::Vector4d point;
	for(int i=0; i<cloud->xyz.size(); i++){
    int kx = static_cast<int>(cloud->xyz[i].x / voxel_size);
    int ky = static_cast<int>(cloud->xyz[i].y / voxel_size);
    int kz = static_cast<int>(cloud->xyz[i].z / voxel_size);
    int key = (kx*2000 + ky)*1000 + kz;
    point << cloud->xyz[i].x, cloud->xyz[i].y, cloud->xyz[i].z, 0;
    grid[key].push_back(point);
	}

  cloudMap::iterator it;
  for(auto it = grid.begin(); it != grid.end(); it++){
		if(it->second.size() > 0){
      Eigen::Vector4d point = it->second[0];
      vec3 xyz = vec3(point(0), point(1), point(2));
			xyz_sampled.push_back(xyz);
		}
	}
*/
  //---------------------------
}

}
