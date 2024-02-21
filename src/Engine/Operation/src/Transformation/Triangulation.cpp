#include "Triangulation.h"

#include <Engine/Operation/Namespace.h>
#include <cstdlib>


namespace ope{

// Constructor / Destructor
Triangulation::Triangulation(){
  //---------------------------


  //---------------------------
}
Triangulation::~Triangulation(){}

//Main function
void Triangulation::make_triangulation(utl::type::Data* data){
  if(data->point.xyz.size() == 0) return;
  if(data->width == -1 || data->height == -1) return;
  //---------------------------

  //Prepare data
  vector<vec3> xyz;
  vector<vec4> rgb;
  vector<float> Is;
  vec3 empty = vec3(0, 0, 0);
  float threshold = 0.5f;

  //Loop
  for(int i=0; i<data->height - 1; i++){
    for(int j=0; j<data->width - 1; j++){
      // Calculate the indices of the four points
      int index_1 = i * data->width + j;
      int index_2 = index_1 + 1;
      int index_3 = (i + 1) * data->width + j;
      int index_4 = index_3 + 1;

      const vec3& point_1 = data->point.xyz[index_1];
      const vec3& point_2 = data->point.xyz[index_2];
      const vec3& point_3 = data->point.xyz[index_3];
      const vec3& point_4 = data->point.xyz[index_4];

      float distance_1_2 = glm::distance(point_1, point_2);
      float distance_1_3 = glm::distance(point_1, point_3);
      float distance_2_3 = glm::distance(point_2, point_3);

      if(point_1 != empty && point_2 != empty && point_3 != empty){
        if(distance_1_2 <= threshold && distance_1_3 <= threshold && distance_2_3 <= threshold){
          xyz.push_back(point_1);
          xyz.push_back(point_3);
          xyz.push_back(point_2);

          rgb.push_back(data->point.rgb[index_1]);
          rgb.push_back(data->point.rgb[index_3]);
          rgb.push_back(data->point.rgb[index_2]);

          Is.push_back(data->point.Is[index_1]);
          Is.push_back(data->point.Is[index_3]);
          Is.push_back(data->point.Is[index_2]);
        }
      }

      float distance_2_4 = glm::distance(point_2, point_4);
      float distance_3_4 = glm::distance(point_3, point_4);

      if(point_2 != empty && point_4 != empty && point_3 != empty){
        if(distance_2_4 <= threshold && distance_3_4 <= threshold && distance_2_3 <= threshold){
          xyz.push_back(point_2);
          xyz.push_back(point_3);
          xyz.push_back(point_4);

          rgb.push_back(data->point.rgb[index_2]);
          rgb.push_back(data->point.rgb[index_3]);
          rgb.push_back(data->point.rgb[index_4]);

          Is.push_back(data->point.Is[index_2]);
          Is.push_back(data->point.Is[index_3]);
          Is.push_back(data->point.Is[index_4]);
        }
      }

    }
  }

  data->draw_type_name = "triangle";
  data->point.xyz = xyz;
  data->point.rgb = rgb;
  data->point.Is = Is;
  data->point.size = xyz.size();

  //---------------------------
}





}
