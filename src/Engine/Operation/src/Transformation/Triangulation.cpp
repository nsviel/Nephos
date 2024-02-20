#include "Triangulation.h"

#include <Engine/Operation/Namespace.h>
#include <cstdlib>


namespace eng::ope{

// Constructor / Destructor
Triangulation::Triangulation(){
  //---------------------------


  //---------------------------
}
Triangulation::~Triangulation(){}

//Main function
void Triangulation::make_triangulation(utl::type::Data* data){
  //---------------------------

  if(data->xyz.size() == 0) return;

  vector<vec3> xyz;
  vector<vec4> rgb;
  vector<float> Is;
  vec3 empty = vec3(0, 0, 0);
  constexpr float max_distance_threshold = 0.2f; // Adjust threshold as needed

  for (size_t i = 0; i < data->xyz.size() - 2; i++) {
      const vec3& point_1 = data->xyz[i];
      const vec3& point_2 = data->xyz[i + 1];
      const vec3& point_3 = data->xyz[i + 2];

      // Calculate distances between adjacent points
      float distance_12 = glm::length(point_2 - point_1);
      float distance_23 = glm::length(point_3 - point_2);
      float distance_31 = glm::length(point_1 - point_3);

      // Check if all distances are below the threshold
      if (distance_12 < max_distance_threshold &&
          distance_23 < max_distance_threshold &&
          distance_31 < max_distance_threshold) {
          // Push back vertices and colors
          xyz.push_back(point_1);
          xyz.push_back(point_2);
          xyz.push_back(point_3);

          rgb.push_back(data->rgb[i]);
          rgb.push_back(data->rgb[i + 1]);
          rgb.push_back(data->rgb[i + 2]);

          Is.push_back(data->Is[i]);
          Is.push_back(data->Is[i + 1]);
          Is.push_back(data->Is[i + 2]);
      }
  }

  /*
  data->draw_type_name = "triangle";
  say("ok");
  data->xyz = xyz;
  data->rgb = rgb;
  data->Is = Is;
  data->nb_point = xyz.size();
  */
  
  //---------------------------
}





}
