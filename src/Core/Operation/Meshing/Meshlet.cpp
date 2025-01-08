#include "Meshlet.h"

#include <Utility/Namespace.h>
#include <meshoptimizer.h>
#include <cstdlib>


namespace ope{

// Constructor / Destructor
Meshlet::Meshlet(){
  //---------------------------


  //---------------------------
}
Meshlet::~Meshlet(){}

//Main function
void Meshlet::compute(utl::base::Data& data){
  //---------------------------

  //Input
  std::vector<glm::vec3>& xyz = data.xyz;
  std::vector<int> vec_indice;

  //Retrieve max number of meshlet
  const size_t max_vertice  = 64;
  const size_t max_triangle = 124;
  const float cone_weight   = 0.0f;
  const size_t max_meshlet = meshopt_buildMeshletsBound(vec_indice.size(), max_vertice, max_triangle);

  //And resize output vectors accordingly
  std::vector<meshopt_Meshlet> vec_meshlet;
  std::vector<uint32_t> vec_vertice;
  std::vector<uint8_t> vec_triangle;
  vec_meshlet.resize(max_meshlet);
  vec_vertice.resize(max_meshlet * max_vertice);
  vec_triangle.resize(max_meshlet * max_triangle * 3);
/*
  size_t nb_meshlet = meshopt_buildMeshlets(
    vec_meshlet.data(),
    vec_vertice.data(),
    vec_triangle.data(),
    reinterpret_cast<const uint32_t*>(mesh.GetTriangles().data()),
    vec_indice.size(),
    reinterpret_cast<const float*>(xyz.data()),
    xyz.size(),
    sizeof(glm::vec3),
    max_vertice,
    max_triangle,
    cone_weight);

  auto& last = vec_meshlet[nb_meshlet - 1];
  vec_vertice.resize(last.vertex_offset + last.vertex_count);
  vec_triangle.resize(last.triangle_offset + ((last.triangle_count * 3 + 3) & ~3));
  vec_meshlet.resize(nb_meshlet);
*/
  //---------------------------
}

}
