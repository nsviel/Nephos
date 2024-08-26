#include "Triangulation.h"

#include <Utility/Namespace.h>
#include <cstdlib>


namespace ope{

// Constructor / Destructor
Triangulation::Triangulation(){
  //---------------------------


  //---------------------------
}
Triangulation::~Triangulation(){}

//Main function
void Triangulation::make_triangulation(utl::base::Data& data){
  if(data.xyz.size() == 0) return;
  if(data.width == -1 || data.height == -1) return;
  //---------------------------
/*
  //Prepare data
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec3> rgb;
  std::vector<float> Is;
  std::vector<glm::vec3> Nxyz_triangle;
  std::vector<glm::vec3> Nxyz_point;
  glm::vec3 empty = glm::vec3(0, 0, 0);
  float threshold = 0.5f;

  //Loop
  #pragma omp parallel for collapse(2) schedule(static)
  for(int i=0; i<data.height - 1; i++){
    for(int j=0; j<data.width - 1; j++){
      // Calculate the indices of the four points
      int index_1 = i * data.width + j;
      int index_2 = index_1 + 1;
      int index_3 = (i + 1) * data.width + j;
      int index_4 = index_3 + 1;

      const glm::vec3& point_1 = data.xyz[index_1];
      const glm::vec3& point_2 = data.xyz[index_2];
      const glm::vec3& point_3 = data.xyz[index_3];
      const glm::vec3& point_4 = data.xyz[index_4];

      float distance_1_2 = glm::distance(point_1, point_2);
      float distance_1_3 = glm::distance(point_1, point_3);
      float distance_2_3 = glm::distance(point_2, point_3);

      if(point_1 != empty && point_2 != empty && point_3 != empty &&
        distance_1_2 <= threshold && distance_1_3 <= threshold && distance_2_3 <= threshold){
        xyz.push_back(point_1);
        xyz.push_back(point_3);
        xyz.push_back(point_2);

        rgb.push_back(data.rgb[index_1]);
        rgb.push_back(data.rgb[index_3]);
        rgb.push_back(data.rgb[index_2]);

        Is.push_back(data.Is[index_1]);
        Is.push_back(data.Is[index_3]);
        Is.push_back(data.Is[index_2]);

        // Compute triangle normal
        glm::vec3 normal = glm::normalize(glm::cross(point_2 - point_1, point_3 - point_1));
        Nxyz_triangle.push_back(normal);
        Nxyz_triangle.push_back(normal);
        Nxyz_triangle.push_back(normal);
        Nxyz_point.push_back(normal);
      }else{
        Nxyz_point.push_back(empty);
      }

      float distance_2_4 = glm::distance(point_2, point_4);
      float distance_3_4 = glm::distance(point_3, point_4);

      if(point_2 != empty && point_4 != empty && point_3 != empty &&
        distance_2_4 <= threshold && distance_3_4 <= threshold && distance_2_3 <= threshold){
          xyz.push_back(point_2);
          xyz.push_back(point_3);
          xyz.push_back(point_4);

          rgb.push_back(data.rgb[index_2]);
          rgb.push_back(data.rgb[index_3]);
          rgb.push_back(data.rgb[index_4]);

          Is.push_back(data.Is[index_2]);
          Is.push_back(data.Is[index_3]);
          Is.push_back(data.Is[index_4]);

          // Compute triangle normal
          glm::vec3 normal = glm::normalize(glm::cross(point_2 - point_1, point_3 - point_1));
          Nxyz_triangle.push_back(normal);
          Nxyz_triangle.push_back(normal);
          Nxyz_triangle.push_back(normal);
          Nxyz_point.push_back(normal);
      }else{
        Nxyz_point.push_back(empty);
      }

    }
  }

  //data.topology.type = utl::topology::TRIANGLE;
  data.xyz = xyz;
  data.rgb = rgb;
  data.Is = Is;
  data.Nxyz = Nxyz_triangle;
  data.size = xyz.size();
  data.Nxyz = Nxyz_point;
*/
  //---------------------------
}

}
