#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Operation/src/Namespace.h>
#include <tsl/robin_map.h>

typedef std::vector<glm::vec3> Voxel;
typedef tsl::robin_map<int, Voxel> Voxel_map;
typedef tsl::robin_map<int, Voxel>::iterator Voxel_map_it;


namespace eng::ope{

class Voxel
{
public:
  // Constructor / Destructor
  Voxel();
  ~Voxel();

public:
  //Main function
  void sub_sampling_subset(utl::type::Data* data);

private:

};

}
